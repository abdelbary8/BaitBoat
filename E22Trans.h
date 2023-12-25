#ifndef __E22Trans_H

#define __E22Trans_H

#include <arduino.h>
#include "CommandParser.h"

enum E22MODE {
	Mode_Transmission   = 0,
	Mode_WOR            = 1,
	Mode_Configuration 	= 2,
	Mode_DeepSleep 			= 3,
};

class E22Trans {
  public:
    E22Trans(commandParser*, HardwareSerial*, byte, byte, byte);
    void init();
    bool isNotReady();
    void setMode(E22MODE);
    void initialConfiguration();
    void sendMessage(byte[], String);
    void waitForSignal();
    
    
  private:
    HardwareSerial * hs;
    byte AUX_PIN;
    byte M1_PIN;
    byte M0_PIN;
    commandParser* cp;
    bool newData = false;
    const static byte numChars = 10;
    char messageReceived[numChars];    
};

#endif

