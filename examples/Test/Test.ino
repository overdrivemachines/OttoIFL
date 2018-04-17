#include <OttoIFL.h>

Otto Otto;

void setup() 
{  
  Otto.init();
  Serial.begin(115200);

  
}

void loop() 
{
	if (Serial.available())
	{
		char command = Serial.read();
		Serial.println("hello0");
	}
	  
}
