#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>

#define N_SERVOS 4
#define Otto_YL 2
#define Otto_YR 3
#define Otto_RL 4
#define Otto_RR 5
#define EEPROM_BASE_ADDRESS 0
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
Oscillator servo[N_SERVOS];
int pick_servo=0;

void setup() {
  Serial.begin(9600);
  servo[0].attach(Otto_YL);
  servo[1].attach(Otto_YR);
  servo[2].attach(Otto_RL);
  servo[3].attach(Otto_RR);

  resetServosTrim();
  resetServos();
  
  printHelp();
  printCommandLine();
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
      case 'h':
        printHelp();
        break;
      case 'p':
        printCommandLine();
        break;
      case 'i':
        printInfo();
        break;
      case 'c':
        chooseServo();
        break;
      case 's':
        saveTrim();
        break;
      case 'l':
        loadTrim();
        break;
      case '+':
      case '-':
        calibration(command);
        break;
    }
  }
}

void resetServosTrim() {
  for (int i=0; i<N_SERVOS; i++) {
    servo[i].SetTrim(0);
  }
}

void resetServos() {
  for (int i=0; i<N_SERVOS; i++) {
    servo[i].SetPosition(90);
  }
}

void chooseServo() {
  int pin = Serial.parseInt();
  if (pin >=2 && pin <= 5) {
    pick_servo = pin-2;
    switch (pin) {
      case 2:
        Serial.print("Otto_YL ");
        break;
      case 3:
        Serial.print("Otto_YR ");
        break;
      case 4:
        Serial.print("Otto_RL ");
        break;
      case 5:
        Serial.print("Otto_RR ");
        break;
    }
    Serial.println("selected");
  }
}

void calibration(char command) {
  if (pick_servo >=0 && pick_servo <= 3) {
    int input = Serial.parseInt();
    int temp = servo[pick_servo].getTrim();
    if (temp-input >= -90 && temp+input <= 90) {
      switch (command) {
        case '+':
          servo[pick_servo].SetTrim(temp+input);
          break;
        case '-':
          servo[pick_servo].SetTrim(temp-input);
          break;
      }
      servo[pick_servo].SetPosition(90);
    }
  }
}

void printHelp() {
  Serial.println("This program calibrates the servo motor.");
  Serial.println("Select the desired servo motor. e.g: c 2");
  Serial.println("How to change data e.g: + 3  or  - 2 etc..");
}

void printCommandLine() {
  Serial.println("=========================================");
  Serial.println("h:help\np:print command list\ni:changed value(trim)\nc:choose servo\n+: input + value\n-: input - value\ns:save trims\nl:load trims");
  Serial.println("=========================================");
}

void saveTrim() {
  for (int i=0; i<N_SERVOS; i++) {
    EEPROM.write(EEPROM_BASE_ADDRESS+i,servo[i].getTrim());
  }
  Serial.println("Trim values saved");
}

void loadTrim() {
  int trim = 0;
  for (int i=0; i<N_SERVOS; i++) {
    trim = EEPROM.read(EEPROM_BASE_ADDRESS + i);
    if (trim > 128) trim -= 256;
    servo[i].SetTrim(trim);
  }
  Serial.println("Trim values loaded");
  resetServos();
}

void printInfo() {
  Serial.print("Otto_YL: ");
  Serial.println(servo[0].getTrim());
  Serial.print("Otto_YR: ");
  Serial.println(servo[1].getTrim());
  Serial.print("Otto_RL: ");
  Serial.println(servo[2].getTrim());
  Serial.print("Otto_RR: ");
  Serial.println(servo[3].getTrim());
}

