#include <OttoIFL.h>
#include <stdio.h>

Otto otto;
int servoTrims[SERVO_COUNT];

void setup() 
{  
  otto.init();
  Serial.begin(115200);
 
  // Serial.println("LL LR FL FR AL AR");

  for (int i = 0; i < SERVO_COUNT; i++) 
  {
    int servo_trim = EEPROM.read(i);
    if (servo_trim > 128)
    {
      servo_trim -= 256;
    }

    servoTrims[i] = servo_trim;

    // Serial.print(servo_trim);
    // Serial.print(" ");
  }

  selectServo();
}

void loop() 
{
	if (Serial.available())
		selectServo();  	
}

void selectServo()
{
	int inputPin = 2;
	int inputTrim = 0;
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

	inputPin = Serial.parseInt();
	inputTrim = Serial.parseInt();
	inputTrim = inputTrim % 90;

	switch(inputPin)
	{
		case LEG_L:
		servoTrims[0] = inputTrim;
		break;

		case LEG_R:
		servoTrims[1] = inputTrim;
		break;

		case FOOT_L:
		servoTrims[2] = inputTrim;
		break;

		case FOOT_R:
		servoTrims[3] = inputTrim;
		break;

		case ARM_L:
		servoTrims[4] = inputTrim;
		break;

		case ARM_R:
		servoTrims[5] = inputTrim;
		break;
	}

	otto.setTrims(servoTrims[0], servoTrims[1], servoTrims[2], servoTrims[3], servoTrims[4], servoTrims[5]);
	otto.saveTrimsOnEEPROM();
}
