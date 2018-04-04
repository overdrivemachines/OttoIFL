/*
 *    LedControlHT.cpp - A library for controlling led matrix displays with a Holtek HT16K33
 *    Copyright (c) 2016 Laurence Crew
 *    
 *    Based on:
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LedControlHT_h
#define LedControlHT_h

#include <avr/pgmspace.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// status array size
// 16 bytes per 16x8 matrix controller
#define STATUS_SIZE	16


class LedControlHT {
    private :

		/* Send out a single command to the device */
		void command(byte addr, byte opcode);

        /* We keep track of the led-status for all devices in this array */
        byte status[STATUS_SIZE];

		/* I2C Address */
		/* Note for multiple devices this needs to be an array; not yet implemented */
		byte _i2cAddr;

        /* The number of connected rows */
        byte _numRows;

		/* The maximum number of devices we use */
        byte maxDevices;

		/* If true, the display is rotated 90 degrees i.e. cols swapped with rows */
        bool isRotated = false;

		/* If true, the rows are flipped */
        bool flipRows = false;

		/* If true, the columns are flipped */
        bool flipCols = false;

		/* Offset the rows by this factor */
        byte rowOffset = 0;

public:
        /* 
         * Create a new controler 
         * Params :
         * i2cAddr		I2C address of the display; 0x70 by default for HT16K33, can be altered with jumpers
		 *   Note: Multiple addresses not yet implemented
         * numRows		number of connected rows from the controller, up to 16
         * numDevices	maximum number of devices that can be controled
         */
        LedControlHT(byte i2cAddr, byte numRows=8, byte numDevices=1);

		/*
		 * begin; initialise i2c & display
		 * Call this from setup(); hangs if called from a class constructor
		 */
		void begin();

        /*
         * Gets the number of devices attached to this LedControl.
         * Returns :
         * byte	the number of devices on this LedControl
         */
        byte getDeviceCount();

        /* 
         * Set the shutdown (power saving) mode for the device
         * Params :
         * addr	The address of the display to control
         * status	If true the device goes into power-down mode. Set to false
         *		for normal operation.
         */
        void shutdown(byte addr, bool status);

        /* 
         * Set the brightness of the display.
         * Params:
         * addr		the address of the display to control
         * intensity	the brightness of the display. (0..15)
         */
        void setIntensity(byte addr, byte intensity);

		/* 
         * Set all displays as rotated (swap columns with rows)
         * Params:
         * status	TRUE = rotated; FALSE = normal
        */
        void setRotated(bool status);

		/* 
         * Set all displays to flip order in rows
         * Params:
         * status	TRUE = flip rows; FALSE = normal
        */
        void setFlipRows(bool status);

		/* 
         * Set all displays to flip order in columns
         * Params:
         * status	TRUE = flip columns; FALSE = normal
        */
        void setFlipCols(bool status);

		/* 
         * Set a row offset for all displays
         * Params:
         * offset	amount to offset the rows
        */
        void setRowOffset(byte offset);

		/* 
         * Clear the status buffer of the display
		 * Note - call refresh() to write to the actual display
         * Params:
         * addr	address of the display to control
         */
        void clearDisplay(byte addr);

        /* 
         * Set the status of a single Led.
         * Params :
         * addr	address of the display 
         * row	the row of the Led (0..7)
         * col	the column of the Led (0..7)
         * state	If true the led is switched on, 
         *		if false it is switched off
         */
        void setLed(byte addr, byte row, byte col, bool state);

        /* 
         * Set all 8 Led's in a row to a new state
         * Params:
         * addr	address of the display
         * row	row which is to be set (0..7)
         * value	each bit set to 1 will light up the
         *		corresponding Led.
         */
        void setRow(byte addr, byte row, byte value);

        /* 
         * Set all 8 Led's in a column to a new state
         * Params:
         * addr	address of the display
         * col	column which is to be set (0..7)
         * value	each bit set to 1 will light up the
         *		corresponding Led.
         */
        void setColumn(byte addr, byte col, word value);

		/*
		 * Render the status array out to the display
         * Params:
         * addr	address of the display
		 */
		 void refresh (byte addr);

};

#endif	//LedControlHT.h



