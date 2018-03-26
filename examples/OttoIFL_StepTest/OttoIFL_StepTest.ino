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
  commandList();
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  if (Serial.available()) {
    String command = Serial.readString();
    command.replace(" ", "");
    int length = command.length();
    String command_1 = command.substring(0, length-1);

    if (command.equals("home")) {
      Serial.println("Otto at rest position");
      Otto.setRestState(false);
      Otto.home();
    } else if (command.equals("jump")) {
      Serial.println("Otto jump");
      Otto.jump(1, 1500);
    } else if (command_1.equals("walk")) {
      int dir = command.substring(length-1, length).toInt();
      if (dir == 1 || dir == 2) {
        if (dir == 2) dir = -1;
        Serial.println("Otto walking");
        Otto.walk(2, 1000, dir);
      }
    } else if (command_1.equals("turn")) {
      int dir = command.substring(length-1, length).toInt();
      if (dir == 1 || dir == 2) {
        if (dir == 2) dir = -1;
        Serial.println("Otto Turning");
        Otto.turn(4, 1500, dir);
      }
    } else if (command_1.equals("bend")) {
      int dir = command.substring(length-1, length).toInt();
      if (dir == 1 || dir == 2) {
        if (dir == 2) dir = -1;
        Serial.println("Otto bend");
        Otto.bend(1, 1500, dir);
      }
    } else if (command_1.equals("shakeLeg")) {
      int dir = command.substring(length-1, length).toInt();
      if (dir == 1 || dir == 2) {
        if (dir == 2) dir = -1;
        Serial.println("Otto shakeLeg");
        Otto.shakeLeg(1, 1500, dir);
      }
    } else if (command.equals("updown")) {
      Serial.println("Otto updown");
      Otto.updown(1, 1500, 15);
    } else if (command.equals("swing")) {
      Serial.println("Otto swing");
      Otto.swing(1, 1500, 15);
    } else if (command.equals("tiptoeSwing")) {
      Serial.println("tiptoeSwing");
      Otto.tiptoeSwing(1, 1500, 15);
    } else if (command.equals("jitter")) {
      Serial.println("Otto jitter");
      Otto.jitter(1, 1500, 15);
    } else if (command.equals("ascendingTurn")) {
      Serial.println("Otto ascendingTurn");
      Otto.ascendingTurn(1, 1500, 15);
    } else if (command_1.equals("moonwalker")) {
      int dir = command.substring(length-1, length).toInt();
      if (dir == 1 || dir == 2) {
        if (dir == 2) dir = -1;
        Serial.println("Otto moonwalker");
        Otto.moonwalker(4, 1500, 15, dir);
      }
    } else if (command_1.equals("crusaito")) {
      int dir = command.substring(length-1, length).toInt();
      if (dir == 1 || dir == 2) {
        if (dir == 2) dir = -1;
        Serial.println("Otto crusaito");
        Otto.crusaito(2, 1500, 15, dir);
      }
    } else if (command_1.equals("flapping")) {
      int dir = command.substring(length-1, length).toInt();
      if (dir == 1 || dir == 2) {
        if (dir == 2) dir = -1;
        Serial.println("Otto flapping");
        Otto.flapping(2, 1500, 15, dir);
      }
    } else if (command.equals("help")) {
      help();
    } else if (command.equals("command")) {
      commandList();
    } else {
      Serial.println("please check the command");
    }
  }
}

void commandList() {
  Serial.println("CommandList");
  Serial.print("home, jump, walk, turn, bend, shakeLeg, updown, swing, tiptoeSwing, ");
  Serial.println("jitter, ascendingTurn, moonwalker, crusaito, flapping, help, command");
}

void help() {
  Serial.println("========================================================");
  Serial.println("The following items require additional parameters.");
  Serial.println("walk, turn, bend, shakeLeg, moonwalker, crusaito, flapping");
  Serial.println("1 means : forward or left, 2 means: backward or right");
  Serial.println("e.g: walk 1 (this means This means walking forward.)");
  Serial.println("========================================================");
}
