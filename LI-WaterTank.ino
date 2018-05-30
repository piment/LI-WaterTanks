#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <HCSR04.h>

const int x = 18; //distance between sensor and higher water level
Adafruit_7segment matrix = Adafruit_7segment();
UltraSonicDistanceSensor distanceSensor(12, 11);

void setup() {
  // put your setup code here, to run once:
  matrix.begin(0x70);
  matrix.setBrightness(15);
  Serial.begin(9600);
}

void loop() {
  
  double dst = distanceSensor.measureDistanceCm();
  dst = round(dst);
  dst = dst - x;
  for(int i = 0; i <= 23; i++){
    if(i < dst < (i + 1)){
      if(dst > 1){
        matrix.blinkRate(0);
        matrix.print(dst * 280.4);
        matrix.writeDisplay();
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
  delay(2000);
  
}
