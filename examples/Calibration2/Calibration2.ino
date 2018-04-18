#include <OttoIFL.h>
#include <stdio.h>

Otto otto;
int servoTrims[SERVO_COUNT];

void printServoTrimsFromEEPROM();
void printMenu();

void setup() 
{  
  otto.init();
  Serial.begin(115200);
  printServoTrimsFromEEPROM();
  printMenu();
}

void loop() 
{
	if (Serial.available())
	{
		int inputPin = 2;
		int inputTrim = 0;

		inputPin = Serial.parseInt();
		inputTrim = Serial.parseInt();
		inputTrim = inputTrim % 90;

		Serial.print(inputPin);
		Serial.print(" ");
		Serial.println(inputTrim);

		switch(inputPin)
		{
			case LEG_L:
			Serial.print("Changing Leg Left from ");
			Serial.print(servoTrims[0]);
			Serial.print(" to ");
			Serial.println(inputTrim);
			servoTrims[0] = inputTrim;
			break;

			case LEG_R:
			Serial.print("Changing Leg Right from ");
			Serial.print(servoTrims[1]);
			Serial.print(" to ");
			Serial.println(inputTrim);
			servoTrims[1] = inputTrim;
			break;

			case FOOT_L:
			Serial.print("Changing Foot Left from ");
			Serial.print(servoTrims[2]);
			Serial.print(" to ");
			Serial.println(inputTrim);
			servoTrims[2] = inputTrim;
			break;

			case FOOT_R:
			Serial.print("Changing Foot Right from ");
			Serial.print(servoTrims[3]);
			Serial.print(" to ");
			Serial.println(inputTrim);
			servoTrims[3] = inputTrim;
			break;

			case ARM_L:
			Serial.print("Changing Arm Left from ");
			Serial.print(servoTrims[4]);
			Serial.print(" to ");
			Serial.println(inputTrim);
			servoTrims[4] = inputTrim;
			break;

			case ARM_R:
			Serial.print("Changing Arm Right from ");
			Serial.print(servoTrims[5]);
			Serial.print(" to ");
			Serial.println(inputTrim);
			servoTrims[5] = inputTrim;
			break;

			default:
			Serial.println("Invalid input");
			break;
		}

		otto.setTrims(servoTrims[0], servoTrims[1], servoTrims[2], servoTrims[3], servoTrims[4], servoTrims[5]);
		otto.saveTrimsOnEEPROM();

		printMenu();			
	}
}

void printServoTrimsFromEEPROM()
{
	Serial.println("LL LR FL FR AL AR");
	for (int i = 0; i < SERVO_COUNT; i++) 
	{
		servoTrims[i] = EEPROM.read(i);
		if (servoTrims[i] > 128)
		{
			servoTrims[i] -= 256;
		}
		Serial.print(servoTrims[i]);
		Serial.print(" ");
	}
	Serial.println("");
}

void printMenu()
{
	Serial.println("======================");
	Serial.println("===Otto Calibration===");
	Serial.println("======================");
	Serial.print("2. Leg Left ");
	Serial.println(servoTrims[0]);
	Serial.print("3. Leg Right ");
	Serial.println(servoTrims[1]);
	Serial.print("4. Foot Left ");
	Serial.println(servoTrims[2]);
	Serial.print("5. Foot Right ");
	Serial.println(servoTrims[3]);
	Serial.print("10. Arm Left ");
	Serial.println(servoTrims[4]);
	Serial.print("11. Arm Right ");
	Serial.println(servoTrims[5]);

	Serial.println("Select a servo and set value. Eg 2 -27");
	
}
