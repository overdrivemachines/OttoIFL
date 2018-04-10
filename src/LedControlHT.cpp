#include "LedControlHT.h"
#include <Wire.h>

// the opcodes for the HT16K33
#define OP_OSC_ON 0x21
#define OP_SHUTDOWN 0x20
#define OP_DISPLAY_ON 0x81
#define OP_DISPLAY_BLINK 0x83
#define OP_INTENSITY 0xE0

LedControlHT::LedControlHT(byte i2cAddr, byte numRows, byte numDevices) 
{
  _i2cAddr = i2cAddr;
  if(numRows <= 0 || numRows > 16)
  {
    numRows = 16;
  }
  _numRows = numRows;
  if(numDevices <= 0 || numDevices > 8)
  {
    numDevices = 8;
  }
  maxDevices = numDevices;
  for(byte i = 0; i < STATUS_SIZE; i++) // clear status array
  {
    status[i] = 0x00;
  }
}

void LedControlHT::begin() 
{
  Wire.begin(); // join i2c bus (address optional for master)
  for(byte i = 0; i < maxDevices; i++)
  {
    clearDisplay(i);
    shutdown(i, true); // we go into shutdown-mode on startup
  }
}

byte LedControlHT::getDeviceCount()
{
  return maxDevices;
}

void LedControlHT::shutdown(byte addr, bool b)
{
  if(addr < 0 || addr >= maxDevices)
  {
    return;
  }
  if(b)
  {
    command(addr, OP_SHUTDOWN);
  } else 
  {
    command(addr, OP_OSC_ON);
    command(addr, OP_DISPLAY_ON);
  }
}

void LedControlHT::setIntensity(byte addr, byte intensity) {
    if(addr<0 || addr >= maxDevices)
        return;
    if(intensity>=0 && intensity<16)	
        command(addr, OP_INTENSITY | intensity);
}

void LedControlHT::setRotated(bool status)
{
  isRotated = status;
}

void LedControlHT::setFlipRows(bool status)
{
  flipRows = status;
}

void LedControlHT::setFlipCols(bool status)
{
  flipCols = status;
}

void LedControlHT::setRowOffset(byte offset)
{
  rowOffset = offset;
}

void LedControlHT::clearDisplay(byte addr)
{
  byte offset;
  if(addr < 0 || addr >= maxDevices)
  {
    return;
  }
  offset = addr * 8;
  for(byte i = 0; i < _numRows; i++) 
  {
    status[offset + i] = 0;
  }
}

void LedControlHT::setLed(byte addr, byte row, byte column, bool state) 
{
  byte offset;
  byte val=0x00;
  byte rowdata = 0;

  if(addr < 0 || addr >= maxDevices)
  {
    return;
  }
  if(row < 0 || row > _numRows - 1 || column < 0 || column > 7)
  {
    return;
  }
  offset = addr * 8;
  val = B10000000 >> column;
  if(state)
  {
    status[offset + row] |= val;
  } else 
  {
    status[offset + row] &= ~val;
  }
}

void LedControlHT::setRow(byte addr, byte row, byte value)
{
  byte offset;
  if(addr < 0 || addr >= maxDevices)
  {
    return;
  }
  if(row < 0 || row > _numRows - 1)
  {
    return;
  }
  offset = addr * 8;
  status[offset + row] = value;
}

void LedControlHT::setColumn(byte addr, byte col, word value)
{
  word val;
  if(addr < 0 || addr >= maxDevices)
  {
    return;
  }
  if(col < 0 || col > 7)
  {
    return;
  }
  for(byte row = 0; row < _numRows; row++)
  {
    val = value >> (_numRows - 1 - row);
    val = val & 0x01;
    setLed(addr, row, col, val);
  }
}

void LedControlHT::command(byte addr, byte opcode)
{
  Wire.beginTransmission(_i2cAddr); // note - multiple displays not yet implemented; addr ignored
  Wire.write(opcode);
  Wire.endTransmission();
}

void LedControlHT::refresh(byte addr)
{
  byte offset;
  if(addr < 0 || addr >= maxDevices)
  {
    return;
  }
  offset = addr * 8;
  Wire.beginTransmission(_i2cAddr);
  Wire.write(0); // Start data address	
  for(byte row=0; row < _numRows; row++)
  {
    word rowdata = 0;
    for(byte col = 0; col < 8; col++)
    {
      if(isRotated) // reorder columns into rows
      {
        rowdata |= ((status[offset+((flipCols ? (7 - col) : col) + rowOffset) % 8] >> (flipRows ? (_numRows - 1 - row) : row)) & 1) << col;
      } else // send rows out as rows
      {
        rowdata |= ((status[offset + (flipRows ? (_numRows - 1 - row) : row)] >> ((flipCols ? (7 - col) : col) + rowOffset) % 8) & 1) << col;
      }
    }
    Wire.write(lowByte(rowdata)); // first 8 columns
    Wire.write(highByte(rowdata)); // next 8 columns
  }
  Wire.endTransmission();
}

