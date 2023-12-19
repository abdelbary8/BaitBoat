#include "CommandParser.h"
#include <string.h>
#include <stdint.h>

void commandParser::addCommand(const char* command, void (*function)(const char*))
{
  strncpy(CommandList[numCommand].command,command,SERIALCOMMANDBUFFER); 
  CommandList[numCommand].function = function; 
  numCommand++; 
}

void commandParser::executeCommand(const char* token){
  char *command = strtok(const_cast<char*>(token), " ");
  char *args = strtok(NULL, " ");

  for (uint8_t i=0; i<numCommand; i++) {
    #ifdef SERIALCOMMANDDEBUG
    Serial.print("Comparing ["); 
    Serial.print(token); 
    Serial.print("] to [");
    Serial.print(CommandList[i].command);
    Serial.println("]");
    #endif
    // Compare the found command against the list of known commands for a match
    if (strncmp(token,CommandList[i].command,SERIALCOMMANDBUFFER) == 0) 
    {
      #ifdef SERIALCOMMANDDEBUG
      Serial.print("Matched Command: "); 
      Serial.println(token);
      #endif
      // Execute the stored handler function for the command
      (*CommandList[i].function)(args); 
      break;
    }
  }
}

