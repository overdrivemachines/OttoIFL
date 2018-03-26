# OttoIFL
Arduino library for controlling the OttoIFL RoBot ...

Mix from OttoDIY opensource Project.  
http://ottodiy.com 

## About this Library
- Arms (Lego Hand Pads)
- Capacitance Touch (ADCTouch)
- WiFi (Esp8266)
- Web App
- Mp3 Audio 
- Led Matrix (i2c)
- RGB Led Nose (NeoPixel)
- mBlocks Extention
- mBlocks Examples (Calibration, Smooth Criminal ...)
- Arduino Library
- Arduino Examples (Calibration, Smooth Criminal ...)

## Installation
coming soon ...

## Hardware
<img src="https://github.com/sfranzyshen/OttoIFL/blob/master/extras/media/connection.png" width="500" align="center">

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
 
## OttoIFL 3D Models:
- https://github.com/sfranzyshen/OttoIFL_3D

## Scratch Programming in mBlock 
- https://github.com/sfranzyshen/OttoIFL_mBlock

## OttoIFL ToDo:
### [Arduino (avr)]
- port mouth code from max7219 to HT16K33
- expand otto for arm gpios (init, and for loops, ...)
- unify the ottoserial and softwareserial (so we don't need seperate version of the programs ... ie _BT)
- expand otto serial commands to use audio (mp3) commands and arm movement functions
- modify predetermined motion functions to use arm movements (home, jump, walk, ...)
- expand predetermined motion functions to have arm only movements ... and new handstand/somersault
- modify predetermined gestures functions to use arm movements and audio (OttoHappy, OttoSuperHappy, ..)
- port legacy smooth criminal movements into otto.c
- port legacy ottodiy and ottodiy plus code to mBlocks (smooth criminal)
- expand legacy ottodiy and ottodiy plus code to use arms and audio functions
### [Arduino (esp8266)]
- emulate bluetooth interface (espsoftserial)
- ESP8266Audio
- WiFi
- HTTPServer
- WebSockets
- Web APP
### [Web App]
- mimic bluetooth app
- javascript
- svg
- websockets
### [3D Modeling]
- DIY: head, body, arms
- PLUS: head, body, arms
- glue on features for hair, eyes, and mouth for several age groups ...  young: barn yard animals  older: super heros and  teen/adult: south park, simpsons, futurama, etc ... 

### [Documentation]
### [Internet Presence]
### [Media Production]

# References
- https://github.com/overdrivemachines/OttoIFL
- https://github.com/sfranzyshen/OttoIFL_mBlock
- https://github.com/OttoDIY/PLUS
- https://github.com/stembotvn/OttoDIY_mBlock_Extension
- https://github.com/OttoDIY/OttoDIY_mBlock_Extension
