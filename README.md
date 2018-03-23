# OttoIFL
Otto DIY+ with arms, mp3 Audio, WiFi, and i2c Led Matrix ...

Mix from OttoDIY opensource Project.  
http://ottodiy.com 

## About this Library
- Arms
- HT16K33 i2c Led Matrix (mouth) ... 
- WiFi ... replace Bluetooth 
- mp3 ... trigger audio samples
- APA106 RGB LED (nose)
- MEMS microphone
- ADCTouch
- mBlocks Examples (Calibration, Smooth Criminal ...)

## Installation
coming soon ...

## Hardware (OttoDIY Plus + Arms + WiFi + mp3 + i2c Led Matrix )
<img src="https://github.com/sfranzyshen/OttoIFL/blob/master/media/connection.png" width="500" align="center">

 |  Component                    | Arduino Pin |
 | --- | --- |
 |                               | D0          |
 |                               | D1          |
 |  Servo Leg left               | D2          |
 |  Servo Leg right              | D3          |
 |  Servo Foot left              | D4          |
 |  Servo Foot right             | D5          |
 |  WiFi / mp3 (ESP-01)    Tx    | D6          |
 |  WiFi / mp3 (ESP-01)    Rx    | D7          |
 |  Ultrasonic Trigger (SRF04)   | D8          |
 |  Ultrasonic Echo (SRF04)      | D9          |
 |  Servo Arm left               | D10         |
 |  Servo Arm right              | D11         |
 |  RGB LED  5mm (APA106)        | D12         |
 |  Piezo Buzzer                 | D13         |
 |  Light sensor (Right)         | A0          |
 |  Light Sensor (Left)          | A1          |
 |  Button 1 / ADCTouch          | A2          |
 |  Button 2 / ADCTouch          | A3          |
 |  LED Matrix (HT16K33)  sda    | A4          |
 |  LED Matrix (HT16K33)  scl    | A5          |
 |  Analog Sound Sensor (MEMS)   | A6          |
 |                               | A7          |
## Scratch Programming in mBlock 

# References
- https://github.com/OttoDIY/PLUS
