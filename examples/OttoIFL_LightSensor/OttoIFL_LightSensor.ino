#include <OttoIFL.h>

Otto otto;

void setup() 
{  
  // put your setup code here, to run once:
  otto.init();
  Serial.begin(9600);

}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  
  Serial.print("Light Left: ");
  Serial.println(otto.getLightLValue());

  delay(1000);
}
