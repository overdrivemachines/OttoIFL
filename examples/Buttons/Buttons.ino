#include <ADCTouch.h>

int ref0;     //reference values to remove offset

void setup() 
{
    // No pins to setup, pins can still be used regularly, although it will affect readings

    Serial.begin(9600);

    //create reference values to account for the capacitance of the pad
    ref0 = ADCTouch.read(A2, 500);
    Serial.print("Ref0 = ");
    Serial.println(ref0);
} 

void loop() 
{
    int value0 = ADCTouch.read(A2);   //no second parameter --> 100 samples

    value0 -= ref0;       //remove offset

    Serial.print("Touched: ");
    if (value0 > 40)
        Serial.print("True ");
    else
        Serial.print("False ");
        //send (boolean) pressed or not pressed
           //use if(value > threshold) to get the state of a button

    Serial.print(value0);             //send actual reading
    Serial.print("\n");

    delay(1000);
}