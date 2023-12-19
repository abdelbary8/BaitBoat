#ifndef __HC12Trans_H

#define ____HC12Trans_H

#include <arduino.h>
#include "CommandParser.h"

class HC12Transceiver{
  public:
    HC12Transceiver(commandParser*, HardwareSerial*, byte);
    void init();
    void enterATCommandMode();
    void enterTransparentMode();
    void setDefaultSettings();
    void waitForSignal();
  private:
    HardwareSerial * serialPort;
    byte RST_PIN;
    commandParser* cp;
    bool newData = false;
    const static byte numChars = 10;
    char messageReceived[numChars];
};

#endif

