#include <OttoIFL.h>

Otto Otto;

void setup() 
{  
  Otto.init();
  Serial.begin(115200);
}

void loop() 
{
  Serial.print("Light Left: ");
  Serial.println(Otto.getLight(LEFT));
  Serial.print("Light Right: ");
  Serial.println(Otto.getLight(RIGHT));
  delay(1000);
}
