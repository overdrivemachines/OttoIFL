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
  //Otto.setTrims(-13, -27, 6, -24);
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  Otto.home();
}
