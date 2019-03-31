#include <FrequencyTimer2.h>

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

// The display buffer
byte HEART[] = { B11111111,B10011001,B00000000,B00000000,B00000000,B10000001,B11000011,B11100111};
byte CONFUSED[] = { B11111111,B11000011,B10111101,B11111101,B11100011,B11101111,B11111111,B11101111};
byte W[] = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
byte A[] = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
byte T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
byte R[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
byte M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};

float timeCount = 0;

// plant sensor
int sensorPin = A0;
int led = 13;
int thresholdUp = 400; // TODO what is a threshold for succulent?
int thresholdDown = 250;

void setup() 
{
    // Open serial port
    Serial.begin(9600);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.
    for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
}

void drawScreen(byte buffer2[])
 { 
   // Turn on each row in series
    for (byte i = 0; i < 8; i++)        // count next row
     {
        digitalWrite(rows[i], HIGH);    //initiate whole row
        for (byte a = 0; a < 8; a++)    // count next row
        {
          // if You set (~buffer2[i] >> a) then You will have positive
          digitalWrite(col[a], (buffer2[i] >> a) & 0x01); // initiate whole column
          
          delayMicroseconds(100);       // uncoment delay for diferent speed of display
          //delayMicroseconds(1000);
          //delay(10);
          //delay(100);
          
          digitalWrite(col[a], 1);      // reset whole column
        }
        digitalWrite(rows[i], LOW);     // reset whole row
        // otherwise last row will intersect with next row
    }
}

void warning() {
  delay(5);
  timeCount += 1;

  if(timeCount <  20) {
    drawScreen(W);
  } else if (timeCount <  40) {
    drawScreen(A);
  } else if (timeCount <  60) {
    drawScreen(T);
  } else if (timeCount <  80) {
    drawScreen(E);
  } else if (timeCount <  100) {
    drawScreen(R);
  } else if (timeCount <  120) {
    drawScreen(R);
  } else if (timeCount <  140) {
    drawScreen(M);
  } else if (timeCount <  160) {
    drawScreen(E);
  } else if (timeCount <  180) {
    drawScreen(ALL);
  } else {
    // back to the start
    timeCount = 0;
  }
}

// initiate the drawing
void loop() {
delay(5);
timeCount += 1;

int sensorValue;
  String DisplayWords;
  
  sensorValue = analogRead(sensorPin);
  
  Serial.println(sensorValue);
  
  if (sensorValue <= thresholdDown){
      
      warning();
  
  } else if (sensorValue >= thresholdUp){ 
      
      drawScreen(HEART);
  
  } else {
      
      drawScreen(CONFUSED);
  
  }
}
