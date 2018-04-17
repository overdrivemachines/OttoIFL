//----------------------------------------------------------------
// Code to put all 4 servos in home position (90 degrees)
//-----------------------------------------------------------------
#include <Servo.h>
#include <EEPROM.h>
#include <OttoIFL.h>
#include <Oscillator.h>
#include "MaxMatrix.h"
#include <US.h>
#include <BatReader.h>
Otto Otto;  //This is Otto!

//---------------------------------------------------------
//-- First step: Configure the pins where the servos are attached
/*
         ---------------
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         ---------------
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
  #define PIN_YL 2 //servo[0]
  #define PIN_YR 3 //servo[1]
  #define PIN_RL 4 //servo[2]
  #define PIN_RR 5 //servo[3]

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
  Otto.home();

  Serial.begin(9600);
  Serial.println("forward:8\nbackward:2\nleft:4\nright:6\nstand:5");
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  if (Serial.available()) {
    int val = Serial.read();
    switch(val-48) {
      case 5:
        Otto.setRestState(false);
        Otto.home();
        Serial.println(val);
        break;
      case 8: //forward
        Otto.walk(1, 1000, 1);
        Serial.println(val);
        break;
      case 2: //backward
        Otto.walk(1, 1500, -1);
        Serial.println(val);
        break;
      case 4: //left
        Otto.turn(1, 2000, 1);
        Serial.println(val);
        break;
      case 6: //right
        Otto.turn(1, 2000, -1);
        Serial.println(val);
        break;
    }
  }
}
