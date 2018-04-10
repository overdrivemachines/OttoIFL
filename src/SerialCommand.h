#ifndef SerialCommand_h
#define SerialCommand_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>

#define SERIALCOMMANDBUFFER     20  
#define MAXSERIALCOMMANDS	20
#define MAXDELIMETER            2

class SerialCommand
{
  public:
    SerialCommand();                            // Constructor
    void clearBuffer();                         // Sets the command buffer to all '\0' (nulls)
    char *next();                               // returns pointer to next token found in command buffer (for getting arguments to commands)
    void readSerial(Stream &stream = Serial);   // Main entry point.  
    void addCommand(const __FlashStringHelper *, void(*)());   // Add commands to processing dictionary
    void addDefaultHandler(void (*function)()); // A handler to call when no valid command received. 
	
  private:
    char inChar;                        // A character read from the serial stream 
    char buffer[SERIALCOMMANDBUFFER];   // Buffer of stored characters while waiting for terminator character
    int  bufPos;                        // Current position in the buffer
    char delim[MAXDELIMETER];           // null-terminated list of character to be used as delimeters for tokenizing (default " ")
    char term;                          // Character that signals end of command (default '\r')
    char *token;                        // Returned token from the command buffer as returned by strtok_r
    char *last;                         // State variable used by strtok_r during processing
    typedef struct _callback
    {
      const __FlashStringHelper *command;
      void (*function)();
    } SerialCommandCallback; // Data structure to hold Command/Handler function key-value pairs
    int numCommand;
    SerialCommandCallback CommandList[MAXSERIALCOMMANDS];   // Actual definition for command/handler array
    void (*defaultHandler)();      // Pointer to the default handler function 
};

#endif //SerialCommand_h
