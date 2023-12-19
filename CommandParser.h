#ifndef __CommandParser_H

#define __CommandParser_H

#define SERIALCOMMANDBUFFER 10
#define MAXSERIALCOMMANDS	  3

class commandParser {
  public:
    void addCommand(const char* command, void (*function)(const char*));
    void executeCommand(const char* token);
    
  private:
    int numCommand = 0;
    typedef struct _callback {
			char command[SERIALCOMMANDBUFFER];
			void (*function)(const char*);
		} SerialCommandCallback;
    SerialCommandCallback CommandList[MAXSERIALCOMMANDS]; 
};

#endif

