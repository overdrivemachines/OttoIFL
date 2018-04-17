#include <OttoIFL.h>

Otto Otto;

void setup() 
{  
  Otto.init();
  Serial.begin(115200);

  
}

void loop() 
{
  Serial.println("Hello");
  delay(1000);
}
