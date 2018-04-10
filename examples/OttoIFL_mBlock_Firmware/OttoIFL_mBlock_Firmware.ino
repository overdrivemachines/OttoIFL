/* OttoIFL mBlock in Scratch Mode firmware
 * Mixed from OttoDIY 
 * 
*/

#include "OttoIFL.h" // OttoIFL Library
#include "SerialCommand.h" // Serial Command Library
#include <SoftwareSerial.h> 

// Make sure the pins for servos are in the right position

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

SoftwareSerial softSerial = SoftwareSerial(PIN_SSRx, PIN_SSTx); // The SoftwareSerial Object
SerialCommand SCmd; // The SerialCommand object (* must be declared before Otto)
Otto Otto;          // my name is Otto! Hello World!

// Global Variables
const char programID[] = "OttoIFL_mBlock";
const char name_fac = '$'; // Factory name
const char name_fir = '#'; // Otto name

// Movement parameters
int T = 1000;              // Initial duration of movement, show the speed
int moveId = 0;            // Type of movement
//int modeId = 0;            // Number of mode
int moveSize = 15;         // Size of movement

int randomDance = 0;
int randomSteps = 0;

bool obstacleDetected = false;

// Setup
void setup()
{
  Serial.begin(115200); // Serial communication initialization USB cable
  softSerial.begin(115200); // Serial communication initialization SoftSerial

  Otto.init();

  randomSeed(analogRead(A6)); // Set a random seed

  // Setup callbacks for SerialCommand commands 
  SCmd.addCommand(F("S"), receiveStop);
  SCmd.addCommand(F("L"), receiveMatrix);
  SCmd.addCommand(F("P"), receiveRGBLED);
  SCmd.addCommand(F("T"), recieveBuzzer);
  SCmd.addCommand(F("M"), receiveMovement);
  SCmd.addCommand(F("H"), receiveGesture);
  SCmd.addCommand(F("K"), receiveSing);
  SCmd.addCommand(F("C"), receiveTrims);
  //SCmd.addCommand(F("F"), requestTrims);FIXME:
  SCmd.addCommand(F("G"), receiveServo);
  SCmd.addCommand(F("R"), receiveName);
  SCmd.addCommand(F("E"), requestName);
  SCmd.addCommand(F("D"), requestDistance);
  SCmd.addCommand(F("N"), requestNoise);
  SCmd.addCommand(F("B"), requestBattery);
  //SCmd.addCommand(F("J"), requestMode); // FIXME: Should we support Modes?
  SCmd.addCommand(F("I"), requestProgramId);
  SCmd.addDefaultHandler(receiveStop);

  // Otto wake up sound!
  Otto.sing(S_connection);
  Otto.home();

  // Send Otto name, programID & battery level.
  requestName();
  requestProgramId();
  requestBattery();

  // Checking battery
  LowBatteryAlarm();
  Otto.sing(S_happy);
  Otto.putNose(255, 0, 0);
  Otto.putMouth(happyOpen);
}

// Loop
void loop()
{
  if(Serial.available() > 0) // Hardware (USB) Serial
  {
    SCmd.readSerial(Serial);
  }

  if(softSerial.available() > 0) // Software (WiFi) Serial
  {
    SCmd.readSerial(softSerial);
  }

  if(Otto.getRestState() == false) // Is Otto moving yet
  {
    move(moveId);
  }
}

// Function to read distance sensor & to actualize obstacleDetected variable
void obstacleDetector()
{
  int distance = Otto.getDistance();
  if(distance < 15)
  {
    obstacleDetected = true;
  }else
  {
    obstacleDetected = false;
  }
}

// Function to receive Stop command.
void receiveStop()
{
  sendAck();
  Otto.home();
  sendFinalAck();
}

// Function to receive LED Matrix commands
void receiveMatrix()
{  
  sendAck();
  Otto.home();
  // Examples of receiveMatrix commands
  // L 000000001000010100100011000000000
  // L 001111111111111111111111111111111
  // L 1
  unsigned long int matrix;
  char *arg;
  char *endstr;
  arg = SCmd.next();
  if(arg != NULL)
  {
    if(strlen(arg) > 2)
    {
      matrix = strtoul(arg, &endstr, 2); // Converts a char string to unsigned long integer
      Otto.putMouth(matrix, false);
    }else
    {
      matrix = atoi(arg);
      Otto.putMouth(matrix, true);
    }
  }else
  {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  }
  sendFinalAck();
}

// Function to receive RGB LED commands
void receiveRGBLED() // Example P 0 255 0 will set the led to green (RGB)
{  
  char *arg; 
  int red = 0;
  int green = 0;
  int blue = 0;
  sendAck(); 
  Otto.home();
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    red = atoi(arg);
  }else
  {
    sendFinalAck();
    return;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    green = atoi(arg);
  }else
  {
    sendFinalAck();
    return;
  }  
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    blue = atoi(arg);
  }else
  {
    sendFinalAck();
    return;
  }
  Otto.putNose(red, green, blue); 
  sendFinalAck();
}

// Function to receive buzzer commands
void recieveBuzzer()
{
  sendAck();
  Otto.home(); 
  bool error = false; 
  int frec;
  int duration; 
  char *arg; 
  arg = SCmd.next(); 
  if(arg != NULL)
  { 
    frec = atoi(arg); // Converts a char string to an integer
  } else
  {
    error = true;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    duration = atoi(arg); 
  }else
  {
    error = true;
  }
  if(error == true)
  {
    //delay(2000);
  }else
  { 
    Otto._tone(frec, duration, 1);   
  }
  sendFinalAck();
}

// Function to receive TRims commands
void receiveTrims()
{  
  sendAck();
  Otto.home(); 
  int trim_LL, trim_LR, trim_FL, trim_FR, trim_AL, trim_AR;

  // C trim_LL trim_LR trim_FL trim_FR
  // C trim_LL trim_LR trim_FL trim_FR trim_AL trim_AR

  bool error = false;
  char *arg;
  arg = SCmd.next();
  if(arg != NULL)
  {
    trim_LL = atoi(arg); // Converts a char string to an integer 
  }else
  {
    error = true;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    trim_LR = atoi(arg);
  }else
  {
    error = true;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    trim_FL = atoi(arg);
  }else
  {
    error = true;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    trim_FR = atoi(arg);
  }else
  {
    error = true;
  }
  if(arg != NULL)
  {
    trim_AL = atoi(arg);
  }else
  {
    trim_AL = 0;
  }
  if(arg != NULL)
  {
    trim_AR = atoi(arg);
  }else
  {
    trim_AR = 0;
  }
  if(error == true)
  {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  }else
  {
    Otto.setTrims(trim_LL, trim_LR, trim_FL, trim_FR, trim_AL, trim_AR);
    Otto.saveTrimsOnEEPROM(); // Save it on EEPROM
  } 
  sendFinalAck();
}

// Function to receive Servo commands
void receiveServo()
{  
  sendAck(); 
  moveId = 30;
  // Definition of Servo command // FIXME:Add arms
  // G  servo_LL servo_LR servo_FL servo_FR servo_AL servo_AR 
  // Example of receiveServo commands
  // G 90 85 96 78 90 90
  bool error = false;
  char *arg;
  int servo_YL, servo_YR, servo_RL, servo_RR;

  arg = SCmd.next();
  if(arg != NULL)
  {
    servo_YL = atoi(arg); 
  }else 
  {
    error = true;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    servo_YR = atoi(arg);
  }else
  {
    error = true;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    servo_RL = atoi(arg);
  }else
  {
    error = true;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    servo_RR = atoi(arg);
  }else
  {
    error = true;
  }
  if(error == true)
  {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  }else
  {
    int servoPos[4] = {servo_YL, servo_YR, servo_RL, servo_RR}; // Update Servo
    Otto._moveServos(200, servoPos); //Move 200ms
  }
  sendFinalAck();
}

//  Function to receive movement commands
void receiveMovement()
{
  sendAck();
  if(Otto.getRestState() == true)
  {
    Otto.setRestState(false);
  }
  // Definition of Movement commands
  // M  MoveID  T   MoveSize  
  char *arg; 
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    moveId = atoi(arg);
  }else
  {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
    moveId = 0; // Stop
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    T = atoi(arg);
  }else
  {
    T = 1000;
  }
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    moveSize = atoi(arg);
  }else
  {
    moveSize = 30;
  }
}


// Function to execute the right movement according the movement command received.///
void move(int moveId)
{
  bool manualMode = false;
  switch(moveId)
  {
    case 0:
      Otto.home();
      break;
    case 1: // M 1 1000 
      Otto.walk(1, T, 1);
      break;
    case 2: 
      Otto.walk(1, T, -1);
      break;
    case 3:
      Otto.turn(1, T, 1);
      break;
    case 4:
      Otto.turn(1, T, -1);
      break;
    case 5:
      Otto.updown(1, T, moveSize);
      break;
    case 6:
      moveSize = 30;
      Otto.moonwalker(1, T, moveSize, 1); // M 20 500 15
      break;
    case 7:
      moveSize = 30;
      Otto.moonwalker(1, T, moveSize, -1);
      break;
    case 8: 
      moveSize = 30;
      Otto.swing(1, T, moveSize);
      break;
    case 9:
      moveSize = 30;
	  Otto.crusaito(1, T, moveSize, 1);
      break;
    case 10:
      moveSize = 30;
	  Otto.crusaito(1, T, moveSize, -1);
      break;
    case 11:
      Otto.jump(1, T);
      break;
    case 12:
      moveSize = 30;
	  Otto.flapping(1, T, moveSize, 1);
      break;
    case 13:
      moveSize = 30;
	  Otto.flapping(1, T, moveSize, -1);
      break;
    case 14:
      moveSize = 30;
	  Otto.tiptoeSwing(1, T, moveSize);
      break;
    case 15:
      Otto.bend(1, T, 1);
      break;
    case 16:
      Otto.bend(1, T, -1);
      break;
    case 17:
      Otto.shakeLeg(1, T, 1);
      break;
    case 18:
      Otto.shakeLeg(1, T, -1);
      break;
    case 19:
      moveSize = 30;
      Otto.jitter(1, T, moveSize);
      break;
    case 20:
      Otto.ascendingTurn(1, T, moveSize);
      break;
    default:
      manualMode = true;
      break;
  }
  if(!manualMode)
  {
    sendFinalAck();
  }
}

//  Function to receive gesture commands
void receiveGesture()
{
  sendAck();
  Otto.home(); 
  // Definition of Gesture commands
  // H  GestureID  
  int gesture = 0;
  char *arg; 
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    gesture = atoi(arg);
  }else
  {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  }
  switch (gesture)
  {
    case 1:
      Otto.playGesture(OttoHappy);
      break;
    case 2:
      Otto.playGesture(OttoSuperHappy);
      break;
    case 3:
      Otto.playGesture(OttoSad);
      break;
    case 4:
      Otto.playGesture(OttoSleeping);
      break;
    case 5:
      Otto.playGesture(OttoFart);
      break;
    case 6:
      Otto.playGesture(OttoConfused);
      break;
    case 7:
      Otto.playGesture(OttoLove);
      break;
    case 8:
      Otto.playGesture(OttoAngry);
      break;
    case 9:
      Otto.playGesture(OttoFretful);
      break;
    case 10:
      Otto.playGesture(OttoMagic);
      break;  
    case 11:
      Otto.playGesture(OttoWave);
      break;   
    case 12:
      Otto.playGesture(OttoVictory);
      break; 
    case 13:
      Otto.playGesture(OttoFail);
      break;         
    default:
      break;
  }
  sendFinalAck();
}

//  Function to receive sing commands
void receiveSing()
{
  sendAck();
  Otto.home(); 
  // Definition of Sing commands
  // K  SingID    
  int sing = 0;
  char *arg; 
  arg = SCmd.next(); 
  if(arg != NULL)
  {sing = atoi(arg);
  }else 
  {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  }
  switch(sing)
  {
    case 1: // K 1
      Otto.sing(S_connection);
      break;
    case 2:
      Otto.sing(S_disconnection);
      break;
    case 3:
      Otto.sing(S_surprise);
      break;
    case 4:
      Otto.sing(S_OhOoh);
      break;
    case 5:
      Otto.sing(S_OhOoh2);
      break;
    case 6:
      Otto.sing(S_cuddly);
      break;
    case 7:
      Otto.sing(S_sleeping);
      break;
    case 8:
      Otto.sing(S_happy);
      break;
    case 9:
      Otto.sing(S_superHappy);
      break;
    case 10:
      Otto.sing(S_happy_short);
      break;
    case 11:
      Otto.sing(S_sad);
      break;
    case 12:
      Otto.sing(S_confused);
      break;
    case 13:
      Otto.sing(S_fart1);
      break;
    case 14:
      Otto.sing(S_fart2);
      break;
    case 15:
      Otto.sing(S_fart3);
      break;
    case 16:
      Otto.sing(S_mode1);
      break;
    case 17:
      Otto.sing(S_mode2);
      break; 
    case 18:
      Otto.sing(S_mode3);
      break;   
    case 19:
      Otto.sing(S_buttonPushed);
      break;
    default:
      break;
  }
  sendFinalAck();
}

// Function to receive Name command
void receiveName()
{
  Otto.home(); 
  char newOttoName[11] = "";   // Variable to store data read from Serial.
  int eeAddress = SERVO_COUNT + 1; // Start location we want the data to be in EEPROM.
  char *arg; 
  arg = SCmd.next(); 
  if(arg != NULL)
  {
    int k = 0;
    while((*arg) && (k < 11)) // Complete newOttoName char string
    { 
      newOttoName[k] = *arg++;
      k++;
    }
    EEPROM.put(eeAddress, newOttoName); 
  }else 
  {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  }
  sendFinalAck();
}

// Function to send Otto's name
void requestName()
{
  Otto.home();
  char actualOttoName[11] = "Otto"; 
  int eeAddress = SERVO_COUNT + 1; // EEPROM address to start reading from
  EEPROM.get(eeAddress, actualOttoName);
  sendStart();
  Serial.print(F("E "));
  Serial.print(actualOttoName);
  softSerial.print(F("E "));
  softSerial.print(actualOttoName);
  sendEnd();
}

// Function to send ultrasonic sensor measure (distance in "cm")
void requestDistance()
{
  Otto.home();
  int distance = Otto.getDistance();
  sendStart();
  Serial.print(F("D "));
  Serial.print(distance);
  softSerial.print(F("D "));
  softSerial.print(distance);
  sendEnd();
}

// Function to send noise sensor measure
void requestNoise()
{
  Otto.home();
  int microphone = Otto.getNoise();
  sendStart();
  Serial.print(F("N "));
  Serial.print(microphone);
  softSerial.print(F("N "));
  softSerial.print(microphone);
  sendEnd();
}

//Function to send battery voltage percent
void requestBattery()
{
  Otto.home();
  // The first read of the batery is often a wrong reading, so we will discard this value. 
  double batteryLevel = Otto.getBatteryLevel();
  sendStart();
  Serial.print(F("B "));
  Serial.print(batteryLevel);
  softSerial.print(F("B "));
  softSerial.print(batteryLevel);
  sendEnd();
}

// Function to send program ID
void requestProgramId()
{
  Otto.home();
  sendStart();
  Serial.print(F("I "));
  Serial.print(programID);
  softSerial.print(F("I "));
  softSerial.print(programID);
  sendEnd();
}

void sendStart()
{
  Serial.print(F("&&"));
  softSerial.print(F("&&"));
}

void sendEnd()
{
  Serial.println(F("%%"));
  Serial.flush();
  softSerial.println(F("%%"));
  softSerial.flush();
}

// Function to send Ack comand (A)
void sendAck()
{
  delay(30);
  sendStart();
  Serial.print(F("A"));
  softSerial.print(F("A"));
  sendEnd();
}

// Function to send final Ack comand (F)
void sendFinalAck()
{
  delay(30);
  sendStart();
  Serial.print(F("F"));
  softSerial.print(F("F"));
  sendEnd();
}

// Functions with animatics
void LowBatteryAlarm()
{
  double batteryLevel = Otto.getBatteryLevel();
  if(batteryLevel < 45)
  {
    Otto.putMouth(thunder);
    Otto.bendTones(880, 2000, 1.04, 8, 3); // A5 = 880
    delay(30);
    Otto.bendTones(2000, 880, 1.02, 8, 3); // A5 = 880
    delay(500);
    Otto.clearMouth();  
  }
}

