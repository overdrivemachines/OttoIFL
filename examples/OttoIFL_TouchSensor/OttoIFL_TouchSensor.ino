#include <OttoIFL.h>

Otto Otto;

void setup() 
{  
  Otto.init();
  Serial.begin(115200);
}

void loop() 
{
  Serial.print("Touch Left: ");
  Serial.println(Otto.getTouch(LEFT));
  Serial.print("Touch Right: ");
  Serial.println(Otto.getTouch(RIGHT));
  delay(1000);
}
