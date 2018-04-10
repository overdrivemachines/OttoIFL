#ifndef Otto_h
#define Otto_h

//-- Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         30

#define SERVO_COUNT 6
#define LEG_L       2       // Servo Leg left
#define LEG_R       3       // Servo Leg right
#define FOOT_L      4       // Servo Foot left
#define FOOT_R      5       // Servo Foot right
#define ARM_L       10      // Servo Arm left
#define ARM_R       11      // Servo Arm right

// SoftwareSerial
#define PIN_SSRx    6  
#define PIN_SSTx    7

// Ultrasonic SRF04
#define PIN_Trigger 8       // Ultrasonic SRF04
#define PIN_Echo    9       // Ultrasonic SRF04

// RGB LED 5mm (APA106)
#define PIN_RGBLED  12

// Piezo Buzzer
#define PIN_Buzzer  13

// Light sensor
#define PIN_LightL          A0
#define PIN_LightR          A1

// ADCTouch/Switch
#define PIN_ADCTouch        A2

// LED Matrix H16K33 / LedControlHK library
#define PIN_SDA             A4
#define PIN_SCL             A5
#define MATRIX_ADDR         0x70
#define MATRIX_BRIGHTNESS   10 // 0=min, 15=max

// Analog Sound Sensor (MEMS)
#define PIN_Noise           A6 

#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>
#include <US.h>
#include <BatReader.h>
#include <Wire.h>
#include <LedControlHT.h>
#include <ADCTouch.h>
#include "Otto_mouths.h"
#include "Otto_sounds.h"
#include "Otto_gestures.h"
#include "OttoSerialCommand.h"
#include <PololuLedStrip.h>

/**
 *                   +-------+
 *                   | () () |
 *                   |       |
 *                   +-------+
 *  ARM_R D11==> +---|       |---+ <== ARM_L D10
 *               +---|       |---+
 *   LEG_R D3==>     |-+   +-|     <== LEG_L D2
 *                   +-+---+-+
 *                   | |   | |
 *  FOOT_R D5==>  +--+-+   +-+--+ <== FOOT_L D4
 *                +--+-+   +-+--+
 */


class Otto
{
  public:
    //-- Otto initialization
    void init(int LL = LEG_L, int LR = LEG_R, 
      int FL = FOOT_L, int FR = FOOT_R,
      bool load_calibration=true,
      int NoiseSensor=PIN_Noise, int Buzzer=PIN_Buzzer, 
      int USTrigger=PIN_Trigger, int USEcho=PIN_Echo, 
      int AL = ARM_L, int AR = ARM_R); //FIXME: Add SoftwareSerial, RGB LED, Light sensors

    //-- Attach & detach functions
    void attachServos();
    void detachServos();

    //-- Oscillator Trims
    void setTrims(int LL, int LR, int FL, int FR, int AL, int AR);
    void saveTrimsOnEEPROM();

    //-- Predetermined Motion Functions
    void _moveServos(int time, int  servo_target[]);
    void oscillateServos(int A[4], int O[4], int T, 
        double phase_diff[4], float cycle);

    //-- HOME = Otto at rest position
    void home();
    bool getRestState();
    void setRestState(bool state);
    
    //-- Predetermined Motion Functions
    void jump(float steps=1, int T = 2000);

    void walk(float steps=4, int T=1000, int dir = FORWARD);
    void turn(float steps=4, int T=2000, int dir = LEFT);
    void bend (int steps=1, int T=1400, int dir=LEFT);
    void shakeLeg (int steps=1, int T = 2000, int dir=RIGHT);

    void updown(float steps=1, int T=1000, int h = 20);
    void swing(float steps=1, int T=1000, int h=20);
    void tiptoeSwing(float steps=1, int T=900, int h=20);
    void jitter(float steps=1, int T=500, int h=20);
    void ascendingTurn(float steps=1, int T=900, int h=20);

    void moonwalker(float steps=1, int T=900, int h=20, int dir=LEFT);
    void crusaito(float steps=1, int T=900, int h=20, int dir=FORWARD);
    void flapping(float steps=1, int T=1000, int h=20, int dir=FORWARD);
    void move(int moveID,int time, int _moveSize);
    //-- Sensors functions
    float getDistance(); //US sensor
    int   getNoise();      //Noise Sensor

    //-- Battery
    double getBatteryLevel();
    double getBatteryVoltage();
    
    //-- Mouth & Animations
    void putMouth(unsigned long int mouth, bool predefined = true);
    void putAnimationMouth(unsigned long int anim, int index);
    void clearMouth();

    //-- Nose  
    void putNose(int red = 0, int green = 0, int blue = 0);
  
    //-- Sounds
    void _tone (float noteFrequency, long noteDuration, int silentDuration);
    void _playNote(float noteFrequency, long noteDuration);
    void bendTones (float initFrequency, float finalFrequency, 
        float prop, long noteDuration, int silentDuration);
    void sing(int songName);

    //-- Gestures
    void playGesture(int gesture);

    //-- SoftwareSerial
    //SoftwareSerial *SerialSoft;
    
    // Light Sensors
    int getLightLValue();
    int getLightRValue();

    // ADCTouch Sensor
    bool isADCTouched();
  private:
    
    LedControlHT ledmatrix = LedControlHT(MATRIX_ADDR, 8, 1);
    void writeMatrix(unsigned long value);

    PololuLedStrip<PIN_RGBLED> rgbled;
    rgb_color rgbled_colors;

    BatReader battery;
    Oscillator servo[SERVO_COUNT];
    US us;

    int servo_pins[SERVO_COUNT];
    int servo_trim[SERVO_COUNT];
    int servo_position[SERVO_COUNT];

    int pinBuzzer;
    int pinNoiseSensor;
    
    unsigned long final_time;
    unsigned long partial_time;
    float increment[4];
   
    bool isOttoResting;

    int ADCTouch_reference; //reference values to remove offset

    unsigned long int getMouthShape(int number);
    unsigned long int getAnimShape(int anim, int index);
    void _execute(int A[4], int O[4], int T, double phase_diff[4], float steps);

};

#endif


