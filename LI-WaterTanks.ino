#include <Adafruit_NeoPixel.h>

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <HCSR04.h>

#define left_stop 10
#define right_stop 9

const int x = 16; //distance between sensor and higher water level
Adafruit_7segment matrix = Adafruit_7segment();
UltraSonicDistanceSensor distanceSensor(11, 12);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(22, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  Serial.begin(9600);
  matrix.begin(0x70);
  matrix.setBrightness(15);
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  digitalWrite(8, 0);
  pinMode(7, OUTPUT);
  digitalWrite(7, 0);
  pinMode(6, OUTPUT);
  digitalWrite(6, 0);
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);
}

void buzz_right(int duration){
  digitalWrite(8, 1);
  //digitalWrite(7, 1);
  for(int i = 0; i <= duration; i++){
    //digitalWrite(6, 1);
    digitalWrite(5, 1);
    delay(1);
    //digitalWrite(6, 0);
    digitalWrite(5, 0);
    delay(1);
  }
  digitalWrite(8, 0);
  //digitalWrite(7, 0);
}

void buzz_left(int duration){
  //digitalWrite(8, 1);
  digitalWrite(7, 1);
  for(int i = 0; i <= duration; i++){
    digitalWrite(6, 1);
    //digitalWrite(5, 1);
    delay(1);
    digitalWrite(6, 0);
    //digitalWrite(5, 0);
    delay(1);
  }
  //digitalWrite(8, 0);
  digitalWrite(7, 0);
}

//Min Level = 39cm
//Max Level = 16cm
void loop() {
  if(digitalRead(left_stop) == 0){
    buzz_left(80);
  }
  if(digitalRead(9) == 0){
    buzz_right(80);
  }
  double dst = distanceSensor.measureDistanceCm();
  //Serial.print(dst);
  //Serial.print(" - ");
  dst = round(dst);
  int dst2 = (int) dst;
  //Serial.println(dst2);
  matrix.print(dst2 - 16);
  matrix.writeDisplay();
  int leds = dst2;
  Serial.print(leds);
  Serial.print(" - ");
  leds = map(leds, x, 39, 3, 16);
  Serial.println(leds);
  for(int i =0; i < 23; i++){
    strip.setPixelColor(i, 0,0,150);
  }
  for(int i =0; i < leds; i++){
    strip.setPixelColor(i, 150,0,0);
  }
  strip.show();
  delay(50);
  /*dst = round(dst);
  dst = dst - x;
  for(int i = 0; i <= 23; i++){
    if(i < dst < (i + 1)){
      if(dst > 1){
        matrix.blinkRate(0);
        matrix.print(dst * 280.4);
        matrix.writeDisplay();
        //buzz(500);
      }
      else{
        matrix.blinkRate(1);
        matrix.writeDigitRaw(0,63);
        matrix.writeDigitRaw(1,63);
        matrix.writeDigitRaw(3,63);
        matrix.writeDigitRaw(4,63);
        matrix.writeDisplay();
      }
    }
  }
  
  //Serial.println(distanceSensor.measureDistanceCm());
  //delay(2000);
  */
}