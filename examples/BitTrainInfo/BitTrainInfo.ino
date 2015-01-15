#include "InterruptSampler.h"


void setup()
{
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  static bool onRising = true; 
  
  Serial.begin(9600);
  Serial.println("Started looking for the 'between block' period. Wait 3 seconds.."); 
  delay(200); // send out last println
  is_startInterrupt1(onRising);
  delay(3000);
  if (is_maxPeriod != 0) {
    is_stopInterrupt();
    Serial.print("The period seems to be less than ");
    Serial.print(is_maxPeriod);
    Serial.println(" microseconds.\n");
    
    is_printSampleStatistics();
    Serial.println();
    Serial.println("Now checking the data line.");
    uint32_t gap = (uint32_t) (0.80*is_maxPeriod);
    for (int i=0; i<20; i++) {
      Serial.print("Started looking for the number of bits with "); Serial.print(gap); Serial.println( " micros 'between block' period");
      delay(200);
      is_startInterrupt2(gap, onRising);
      
      uint32_t then = micros();
      uint32_t now = micros();
      while ( (!is_isDone()) && (now-then < 2000000)) {
        delay(100);
        now = micros();
      }
      if (is_isDone()) {
        Serial.print("Number of bits = "); Serial.print(is_currentBit); Serial.println();
      } else {
        Serial.print("Didn't finish: is_currentBit:"); Serial.print(is_currentBit); is_printState(); Serial.println();
        is_printSampleStatistics();
      }
    }
    Serial.println("\nIf the 'Number of bits' above looks consistent then it's probably the correct number.");
    Serial.println("You will have to figure out if the interrupt is on rising or falling edge by yourself.");
    Serial.println("Bye.");
  } else {
    Serial.println("No clock signal was detected, is the clock line attached? (quitting)");
  }
}

void loop() {  
  delay(10);
}
