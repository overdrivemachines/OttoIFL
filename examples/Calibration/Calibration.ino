#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>

#define N_SERVOS 6
// #define Otto_YL 2
// #define Otto_YR 3
// #define Otto_RL 4
// #define Otto_RR 5
#define LEG_L       2       // Servo Leg left
#define LEG_R       3       // Servo Leg right
#define FOOT_L      4       // Servo Foot left
#define FOOT_R      5       // Servo Foot right
#define ARM_L       10      // Servo Arm left
#define ARM_R       11      // Servo Arm right

#define EEPROM_BASE_ADDRESS 0
/**
 *                   +-------+
 *                   | () () |
 *                   |       |
 *                   +-------+
 *  ARM_R D11==> +---|       |---+ <== ARM_L D10
 *               +---|       |---+
 *   LEG_R D3==>     |-+   +-|     <== LEG_L D2
 *                   +-+---+-+
 *                   | |   | |
 *  FOOT_R D5==>  +--+-+   +-+--+ <== FOOT_L D4
 *                +--+-+   +-+--+
 */
Oscillator servo[N_SERVOS];
int pick_servo = 0;

void setup() 
{
  Serial.begin(115200);
  servo[0].attach(LEG_L);
  servo[1].attach(LEG_R);
  servo[2].attach(FOOT_L);
  servo[3].attach(FOOT_R);
  servo[4].attach(ARM_L);
  servo[5].attach(ARM_R);

  resetServosTrim();
  resetServos();
  
  printHelp();
  printCommandLine();
}

void loop() 
{
  if (Serial.available()) 
  {
    char command = Serial.read();
    switch (command) 
    {
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
        Serial.println(command);
        Serial.println("=======");
        calibration(command);
        break;
    }
  }
}

void resetServosTrim() 
{
  for (int i = 0; i < N_SERVOS; i++) 
  {
    servo[i].SetTrim(0);
  }
}

void resetServos() 
{
  for (int i = 0; i < N_SERVOS; i++) 
  {
    servo[i].SetPosition(90);
  }
}

void chooseServo() 
{
  int pin = Serial.parseInt();

  if (((pin >= 2) && (pin <= 5)) || (pin == 10) || (pin == 11))
  {
    // pick_servo = pin-2;
    pick_servo = pin;
    switch (pin)
    {
      case 2:
        Serial.print("Otto Leg Left ");
        break;
      case 3:
        Serial.print("Otto Leg Right ");
        break;
      case 4:
        Serial.print("Otto Foot Left ");
        break;
      case 5:
        Serial.print("Otto Foot Right ");
        break;
      case 10:
        Serial.print("Otto Arm Left ");
        break;
      case 11:
        Serial.print("Otto Arm Right ");
        break;
    }
    Serial.println("selected");

    Serial.println("+[value] or -[value]");
    Serial.println("Eg: +5");
    Serial.println("Eg: -8");
  }
}

void calibration(char command) 
{
  if (((pick_servo >= 2) && (pick_servo <= 5)) || (pick_servo == 10) || (pick_servo == 11)) 
  {
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

void printHelp() 
{
  Serial.println("This program calibrates the servo motor.");
  Serial.println("Select the desired servo motor. e.g: c 2");
  Serial.println("How to change data e.g: + 3  or  - 2 etc..");
}

void printCommandLine() 
{
  Serial.println("=========================================");
  Serial.println("h:help");
  Serial.println("p:print command list");
  Serial.println("i:changed value(trim)");
  Serial.println("c:choose servo");
  Serial.println("    2 - Leg Left");
  Serial.println("    3 - Leg Right");
  Serial.println("    4 - Foot Left");
  Serial.println("    5 - Foot Right");
  Serial.println("    10 - Arm Left");
  Serial.println("    11 - Arm Right");
  Serial.println("+: input + value");
  Serial.println("-: input - value");
  Serial.println("s:save trims");
  Serial.println("l:load trims");
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
  Serial.print("Otto LEG_L: ");
  Serial.println(servo[0].getTrim());
  Serial.print("Otto LEG_R: ");
  Serial.println(servo[1].getTrim());
  Serial.print("Otto FOOT_L: ");
  Serial.println(servo[2].getTrim());
  Serial.print("Otto FOOT_R: ");
  Serial.println(servo[3].getTrim());
  Serial.print("Otto ARM_L: ");
  Serial.println(servo[4].getTrim());
  Serial.print("Otto ARM_R: ");
  Serial.println(servo[5].getTrim());
}

