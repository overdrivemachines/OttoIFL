#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SerialCommand.h"
#include <string.h>

// Constructor makes sure some things are set. 
SerialCommand::SerialCommand()
{
  strncpy(delim, " ", MAXDELIMETER); // strtok_r needs a null-terminated string
  numCommand = 0;                    // Number of callback handlers installed
  clearBuffer();
}

// Initialize the command buffer being processed to all null characters
void SerialCommand::clearBuffer()
{
  for (int i = 0; i < SERIALCOMMANDBUFFER; i++)
  {
    buffer[i] = '\0';
  }
  bufPos = 0;
}

// Retrieve the next token ("word" or "argument") from the Command buffer.
// returns a NULL if no more tokens exist.
char *SerialCommand::next()
{
  char *nextToken;
  nextToken = strtok_r(NULL, delim, &last);
  return nextToken;
}

// This checks the Serial stream for characters, and assembles them into a buffer.  
// When the terminator character (default '\r') is seen, it starts parsing the 
// buffer for a prefix command, and calls handlers setup by addCommand() member
void SerialCommand::readSerial(Stream &stream)
{
  bool onlyOneCommand = true;
  while((stream.available() > 0) && (onlyOneCommand == true))
  {
    int i;
    boolean matched;
    inChar = stream.read();   // Read single available character, there may be more waiting
    if((inChar == '\n') || (inChar == '\r')) // Check for the terminator meaning end of command
    {     
      onlyOneCommand = false;
      bufPos = 0; // Reset to start of buffer
      token = strtok_r(buffer, delim, &last); // Search for command at start of buffer
      if(token == NULL)
      {
        return;
      }
      matched = false;
      for(i = 0; i < numCommand; i++)
      {
        // Compare the found command against the list of known commands for a match
        if(strncmp_P(token, (const char*)CommandList[i].command, SERIALCOMMANDBUFFER) == 0)
        {
          // Execute the stored handler function for the command
          (*CommandList[i].function)();
          clearBuffer();
          matched = true;
          break;
        }
      }
      if(matched == false)
      {
        (*defaultHandler)();
        clearBuffer();
      }
    }
    if(isprint(inChar)) // Only printable characters into the buffer
    {
      buffer[bufPos++] = inChar;   // Put character into buffer
      buffer[bufPos] = '\0';       // Null terminate
      if(bufPos >= SERIALCOMMANDBUFFER)
      {
        bufPos = 0; // wrap buffer around if full
      }
    }
  }
}

// Adds a "command" and a handler function to the list of available commands.
// This is used for matching a found token in the buffer, and gives the pointer
// to the handler function to deal with it.
void SerialCommand::addCommand(const __FlashStringHelper *command, void (*function)())
{
  if(numCommand < MAXSERIALCOMMANDS)
  {
    CommandList[numCommand].command = command;
    CommandList[numCommand].function = function;
    numCommand++;
  }
}

// This sets up a handler to be called in the event that the receveived command string
// isn't in the list of things with handlers.
void SerialCommand::addDefaultHandler(void (*function)())
{
  defaultHandler = function;
}

