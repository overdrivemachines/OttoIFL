#ifndef Otto_h
#define Otto_h

// Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         30

// Servos
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

// Light sensors
#define PIN_LightL  A0
#define PIN_LightR  A1

// Touch sensors
#define PIN_TouchL  A2
#define PIN_TouchR  A3

// LED Matrix H16K33 
#define PIN_SDA     A4
#define PIN_SCL     A5
#define MATRIX_ADDR 0x70
#define MATRIX_BRIGHTNESS 10 // 0 = min 15 = max

// Analog Sound Sensor (MEMS)
#define PIN_Noise   A6 

// Home Switch
#define PIN_HomeButton A7

// Mouths sorted by numbers, and after, by happy to sad mouths
#define zero           0
#define one            1                
#define two            2               
#define three          3  
#define four           4
#define five           5 
#define six            6 
#define seven          7  
#define eight          8 
#define nine           9
#define smile          10                  
#define happyOpen      11  
#define happyClosed    12  
#define heart          13
#define bigSurprise    14  
#define smallSurprise  15
#define tongueOut      16
#define vamp1          17  
#define vamp2          18  
#define lineMouth      19
#define confused       20  
#define diagonal       21          
#define sad            22
#define sadOpen        23 
#define sadClosed      24
#define okMouth        25 
#define xMouth         26
#define interrogation  27
#define thunder        28
#define culito         29
#define angry          30  

// MOUTH ANIMATIONS
#define littleUuh       0
#define littleUuh_size  8  
#define dreamMouth      1
#define dreamMouth_size 4      
#define adivinawi       2
#define adivinawi_size  6
#define wave            3
#define wave_size       10

// Sounds Notes
#define note_C0  16.35    //C0
#define note_Db0 17.32    //C#0/Db0
#define note_D0  18.35    //D0
#define note_Eb0 19.45    //D#0/Eb0
#define note_E0  20.6     //E0
#define note_F0  21.83    //F0
#define note_Gb0 23.12    //F#0/Gb0
#define note_G0  24.5     //G0
#define note_Ab0 25.96    //G#0/Ab0
#define note_A0  27.5     //A0
#define note_Bb0 29.14    //A#0/Bb0
#define note_B0  30.87    //B0
#define note_C1  32.7     //C1
#define note_Db1 34.65    //C#1/Db1
#define note_D1  36.71    //D1
#define note_Eb1 38.89    //D#1/Eb1
#define note_E1  41.2     //E1
#define note_F1  43.65    //F1
#define note_Gb1 46.25    //F#1/Gb1
#define note_G1  49       //G1
#define note_Ab1 51.91    //G#1/Ab1
#define note_A1  55       //A1
#define note_Bb1 58.27    //A#1/Bb1
#define note_B1  61.74    //B1
#define note_C2  65.41    //C2 (Middle C)
#define note_Db2 69.3     //C#2/Db2
#define note_D2  73.42    //D2
#define note_Eb2 77.78    //D#2/Eb2
#define note_E2  82.41    //E2
#define note_F2  87.31    //F2
#define note_Gb2 92.5     //F#2/Gb2
#define note_G2  98       //G2
#define note_Ab2 103.83   //G#2/Ab2
#define note_A2  110      //A2
#define note_Bb2 116.54   //A#2/Bb2
#define note_B2  123.47   //B2
#define note_C3  130.81   //C3
#define note_Db3 138.59   //C#3/Db3
#define note_D3  146.83   //D3
#define note_Eb3 155.56   //D#3/Eb3
#define note_E3  164.81   //E3
#define note_F3  174.61   //F3
#define note_Gb3 185      //F#3/Gb3
#define note_G3  196      //G3
#define note_Ab3 207.65   //G#3/Ab3
#define note_A3  220      //A3
#define note_Bb3 233.08   //A#3/Bb3
#define note_B3  246.94   //B3
#define note_C4  261.63   //C4
#define note_Db4 277.18   //C#4/Db4
#define note_D4  293.66   //D4
#define note_Eb4 311.13   //D#4/Eb4
#define note_E4  329.63   //E4
#define note_F4  349.23   //F4
#define note_Gb4 369.99   //F#4/Gb4
#define note_G4  392      //G4
#define note_Ab4 415.3    //G#4/Ab4
#define note_A4  440      //A4
#define note_Bb4 466.16   //A#4/Bb4
#define note_B4  493.88   //B4
#define note_C5  523.25   //C5
#define note_Db5 554.37   //C#5/Db5
#define note_D5  587.33   //D5
#define note_Eb5 622.25   //D#5/Eb5
#define note_E5  659.26   //E5
#define note_F5  698.46   //F5
#define note_Gb5 739.99   //F#5/Gb5
#define note_G5  783.99   //G5
#define note_Ab5 830.61   //G#5/Ab5
#define note_A5  880      //A5
#define note_Bb5 932.33   //A#5/Bb5
#define note_B5  987.77   //B5
#define note_C6  1046.5   //C6
#define note_Db6 1108.73  //C#6/Db6
#define note_D6  1174.66  //D6
#define note_Eb6 1244.51  //D#6/Eb6
#define note_E6  1318.51  //E6
#define note_F6  1396.91  //F6
#define note_Gb6 1479.98  //F#6/Gb6
#define note_G6  1567.98  //G6
#define note_Ab6 1661.22  //G#6/Ab6
#define note_A6  1760     //A6
#define note_Bb6 1864.66  //A#6/Bb6
#define note_B6  1975.53  //B6
#define note_C7  2093     //C7
#define note_Db7 2217.46  //C#7/Db7
#define note_D7  2349.32  //D7
#define note_Eb7 2489.02  //D#7/Eb7
#define note_E7  2637.02  //E7
#define note_F7  2793.83  //F7
#define note_Gb7 2959.96  //F#7/Gb7
#define note_G7  3135.96  //G7
#define note_Ab7 3322.44  //G#7/Ab7
#define note_A7  3520     //A7
#define note_Bb7 3729.31  //A#7/Bb7
#define note_B7  3951.07  //B7
#define note_C8  4186.01  //C8
#define note_Db8 4434.92  //C#8/Db8
#define note_D8  4698.64  //D8
#define note_Eb8 4978.03  //D#8/Eb8

// Sounds
#define S_connection      0
#define S_disconnection   1
#define S_buttonPushed    2
#define S_mode1           3
#define S_mode2           4
#define S_mode3           5
#define S_surprise        6
#define S_OhOoh           7
#define S_OhOoh2          8
#define S_cuddly          9
#define S_sleeping        10
#define S_happy           11
#define S_superHappy      12
#define S_happy_short     13
#define S_sad             14
#define S_confused        15
#define S_fart1           16
#define S_fart2           17
#define S_fart3           18

// Gestures
#define OttoHappy         0
#define OttoSuperHappy    1
#define OttoSad           2
#define OttoSleeping      3
#define OttoFart          4
#define OttoConfused      5
#define OttoLove          6
#define OttoAngry         7
#define OttoFretful       8
#define OttoMagic         9
#define OttoWave          10
#define OttoVictory       11
#define OttoFail          12

#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>
#include "Oscillator.h"
#include "US.h"
#include "BatReader.h"
#include "LedControlHT.h"
#include "PololuLedStrip.h"
#include "Touch.h"

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

    // Otto initialization
    void init(int LL = LEG_L, int LR = LEG_R, 
              int FL = FOOT_L, int FR = FOOT_R,
              bool load_calibration = true,
              int NoiseSensor = PIN_Noise, int Buzzer = PIN_Buzzer, 
              int USTrigger = PIN_Trigger, int USEcho = PIN_Echo, 
              int AL = ARM_L, int AR = ARM_R); // FIXME: Add RGB LED, Light sensors, ...

    // Attach & detach functions
    void attachServos();
    void detachServos();

    // Oscillator Trims
    void setTrims(int LL = 0, int LR  = 0, int FL = 0, int FR = 0, int AL = 0, int AR = 0);
    //int  getTrim(int servo_target = 0);
    void saveTrimsOnEEPROM();

    // HOME = Otto at rest position
    void home();
    bool getRestState();
    void setRestState(bool state);
    
    // Predetermined Motion Functions
    void _moveServos(int time, int servo_target[]);
    void oscillateServos(int A[SERVO_COUNT], int O[SERVO_COUNT], int T, double phase_diff[SERVO_COUNT], float cycle);
    void jump(float steps = 1, int T = 2000);
    void walk(float steps = 4, int T = 1000, int dir = FORWARD);
    void turn(float steps = 4, int T = 2000, int dir = LEFT);
    void bend (int steps = 1, int T = 1400, int dir = LEFT);
    void shakeLeg (int steps = 1, int T = 2000, int dir = RIGHT);
    void updown(float steps = 1, int T = 1000, int h = 20);
    void swing(float steps = 1, int T = 1000, int h = 20);
    void tiptoeSwing(float steps = 1, int T = 900, int h = 20);
    void jitter(float steps = 1, int T = 500, int h = 20);
    void ascendingTurn(float steps = 1, int T = 900, int h = 20);
    void moonwalker(float steps = 1, int T = 900, int h=20, int dir = LEFT);
    void crusaito(float steps = 1, int T = 900, int h = 20, int dir = FORWARD);
    void flapping(float steps = 1, int T = 1000, int h = 20, int dir = FORWARD);
    void move(int moveID,int time, int _moveSize);

    // Sensors functions
    float getDistance();            // Ultrasonic Sensor
    int   getNoise();               // Noise Sensor
    int   getLight(int direction = LEFT); // Light Sensors 
    bool  getTouch(int direction = LEFT); // Capacitive Touch Sensor
    bool  getHomeButton();

    // Battery
    double getBatteryLevel(); // Percent
    double getBatteryVoltage(); // Voltage
    
    // Mouth & Animations
    void putMouth(unsigned long int mouth, bool predefined = true);
    void putAnimationMouth(unsigned long int anim, int index);
    void clearMouth();

    // Nose  
    void putNose(int red = 0, int green = 0, int blue = 0);
  
    // Sounds
    void _tone (float noteFrequency, long noteDuration, int silentDuration);
    void _playNote(float noteFrequency, long noteDuration);
    void bendTones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    void sing(int songName);

    // Gestures
    void playGesture(int gesture);

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
    float increment[SERVO_COUNT];
    bool isOttoResting;
    int TouchL_reference;
    int TouchR_reference;
    unsigned long int getMouthShape(int number);
    unsigned long int getAnimShape(int anim, int index);
    void _execute(int A[SERVO_COUNT], int O[SERVO_COUNT], int T, double phase_diff[SERVO_COUNT], float steps);
};

#endif


