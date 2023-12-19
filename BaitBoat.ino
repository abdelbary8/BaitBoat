/*

Stearing Change
Purpose:    Control Servo Motor PWM based (value: 0~255)
Syntax:     st PWM_VALUE
Example:    st 75
Response:   none

Speed Change
Purpose:    Control 775 DC Motors PWM based (value: 0~255)
Syntax:     sp PWM_VALUE
Example:    sp 255
Response:   none


Navigate to specific coordinate
Purpose:    Navigate to specific point
Syntax:     nt POINT_LNG, POINT_LAT
Example:    nt 25.265024, 55.311913
Response:   none


Return to Departure Coordinate
Purpose:    Return to Departure Coordinate
Syntax:     nt 0
Example:    nt 0
Response:   none

*/

#define SERIALCOMMANDDEBUG

#include <HardwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "CommandParser.h"
#include "HC12Trans.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
HardwareSerial SerialPort2(2);


void stCommand(const char *args){
  #ifdef SERIALCOMMANDDEBUG
  Serial.print("Stearing PWM New Value: ");
  Serial.println(args);
  #endif

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stearing ");
  lcd.print(args);
}

void spCommand(const char* args){
  #ifdef SERIALCOMMANDDEBUG
  Serial.print("Speed PWM New Value: ");
  Serial.println(args);
  #endif

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed ");
  lcd.print(args);
}

void ntCommand(const char* args){
  #ifdef SERIALCOMMANDDEBUG
  Serial.print("Navigate to Coordinates: ");
  Serial.println(args);
  #endif

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Navigate to ");
  lcd.print(args);
}

commandParser cp;
HC12Transceiver hc12(&cp, &SerialPort2, 5);

void setup() {
  Serial.begin(9600);
  SerialPort2.begin(9600, SERIAL_8N1, 16, 17);
  // delay(80);
  cp.addCommand("st", stCommand);
  cp.addCommand("sp", spCommand);
  cp.addCommand("nt", ntCommand);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Listening...");

  
/*
  const char* token1 = "nt 25.265024,55.311913";
  cp.executeCommand(const_cast<char*>(token1));

  const char* token2 = "sp 255";
  cp.executeCommand(const_cast<char*>(token2));

  const char* token3 = "st 30";
  cp.executeCommand(const_cast<char*>(token3));
*/
}
//--------------------------------------
void loop() {
  hc12.waitForSignal();

}
