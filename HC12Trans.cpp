#include "HC12Trans.h"


HC12Transceiver::HC12Transceiver(commandParser* cpi, HardwareSerial* serial, byte RSTPIN){
  this->serialPort = serial;
  this->RST_PIN = RSTPIN;
  this->cp = cpi;
  init();
}
//---------------------------------
void HC12Transceiver::init(){
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, HIGH);
}
//---------------------------------

void HC12Transceiver::enterATCommandMode(){
  digitalWrite(RST_PIN, LOW);
}
//---------------------------------

void HC12Transceiver::enterTransparentMode(){
  digitalWrite(RST_PIN, HIGH);
  delay(200);
}
//---------------------------------

void HC12Transceiver::setDefaultSettings(){
  this->enterATCommandMode();
  serialPort->print(F("AT+DEFAULT\r\n")); // 9600, CH1, FU3, (F) to bypass flash memory
  delay(100);
  this->enterTransparentMode();
}
//---------------------------------

void HC12Transceiver::waitForSignal(){
  static byte ndx = 0;
  char endMarker = '\n';
  char charReceived;

  if (serialPort->available() > 0) {
    while (serialPort->available() > 0)
    {
      charReceived = serialPort->read();
      if (charReceived != endMarker) 
      {
        messageReceived[ndx] = charReceived;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else
      {
        Serial.println("incoming message");
        messageReceived[ndx] = '\0';
        ndx = 0;
        #ifdef SERIALCOMMANDDEBUG
        Serial.print("Mesage Received: ");
        Serial.println(messageReceived);
        #endif
        this->cp->executeCommand(const_cast<char*>(messageReceived));
      }
    }
  }
}
// int x=5; int &y=x; y=10; .
// int *z=&x;   *z=10; ->
//---------------------------------
