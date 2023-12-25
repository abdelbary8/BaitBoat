#include "E22Trans.h"

E22Trans::E22Trans(commandParser* cpi, HardwareSerial* serial, byte AUXPIN, byte M1PIN, byte M0PIN){
    this->hs = serial;
    this->cp = cpi;
    this->AUX_PIN = AUXPIN;
    this->M1_PIN = M1PIN;
    this->M0_PIN = M0PIN;
    init();
}

void E22Trans::init(){
    pinMode(this->AUX_PIN, INPUT);
    pinMode(this->M1_PIN, OUTPUT);
    pinMode(this->M0_PIN, OUTPUT);
    
    //this->setMode(Mode_Configuration);
    //this->initialConfiguration();
    this->setMode(Mode_Transmission);
}

bool E22Trans::isNotReady(){
    while(digitalRead(this->AUX_PIN) == LOW){
        //1ms is the waiting time for the AUX pin status changes as per datasheet
        delay(1);
    }
    return true;
}

void E22Trans::setMode(E22MODE mode){
    while(this->isNotReady()){}

    switch (mode)
    {
    case Mode_Transmission:
        digitalWrite(M1_PIN, LOW);
        digitalWrite(M0_PIN, LOW);
        break;
    case Mode_WOR:
        digitalWrite(M1_PIN, LOW);
        digitalWrite(M0_PIN, HIGH);
        break;
    case Mode_Configuration:
        digitalWrite(M1_PIN, HIGH);
        digitalWrite(M0_PIN, LOW);
        break;
    case Mode_DeepSleep:
        digitalWrite(M1_PIN, HIGH);
        digitalWrite(M0_PIN, HIGH);
        break;
    default:
        break;
    }
    //2ms is required to wait after mode change as per datasheet
    delay(2);
}

void E22Trans::initialConfiguration(){

}

void E22Trans::sendMessage(byte targetAddressAndChannel[], String message)
{
  while(this->isNotReady()){}

  byte dataByteArray[message.length() + 1];
  message.getBytes(dataByteArray, message.length() + 1);

  this->hs->write(targetAddressAndChannel, sizeof(targetAddressAndChannel));
  this->hs->write(dataByteArray, sizeof(dataByteArray));
  this->hs->println();

}

void E22Trans::waitForSignal()
{
  while(this->isNotReady()){}
  
  static byte ndx = 0;
  char endMarker = '\n';
  char charReceived;

  if (this->hs->available() > 0) {
    while (this->hs->available() > 0)
    {
      charReceived = this->hs->read();
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