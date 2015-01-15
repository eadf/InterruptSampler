#include "InterruptSampler.h"

/**
 * This piece of code displays the output of a cheap Chinese digital dial connected to pin 2(clock) and pin3 (data)
 * The dial seems to operate on such a speed that a 3.3V 8Mhz Arduino Pro Mini can't keep up.
 * So i've tested this on a Arduion Due.
 */
static const float CONVERT_TO_MM = 0.00012396187818742283;  // random magic number converts to mm
static const uint32_t BIT_TRAIN_IDLE_PERIOD = 100000;
static const uint32_t NUMBER_OF_BITS = 43;
static const bool ON_RISING = false;
static const bool NEGATIVE_LOGIC = false;

void setup()
{
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
  if (NEGATIVE_LOGIC) {
    is_startInterrupt3(BIT_TRAIN_IDLE_PERIOD, NUMBER_OF_BITS, !ON_RISING);
  } else {
    is_startInterrupt3(BIT_TRAIN_IDLE_PERIOD, NUMBER_OF_BITS, ON_RISING);
  }
}

float adjustForDial(uint32_t val) {
  int32_t adjusted = val;
  if (NEGATIVE_LOGIC) {
    adjusted = ~val;
  }
  return CONVERT_TO_MM *adjusted;
}

void printResult() {
  uint32_t res1 = is_assembleResult(0,23, true);
  uint32_t res2 = is_assembleResult(24,42, true);
  float result = adjustForDial(res2);
  Serial.print("Result: ");
  Serial.print(" res1="); // this is the 'raw' measurement
  is_printBinary32(res1);
  Serial.print(" res2="); // this is the 'zero adjusted' measurement
  is_printBinary32(res2);
  Serial.print(" "); Serial.print(result,6); Serial.print("mm");
  Serial.print(" currbit="); Serial.println(is_currentBit);
}

void loop()
{  
  if (is_isDone()) {  
    delay(10);
    printResult();
    delay(1000);
    if (NEGATIVE_LOGIC) {
      is_startInterrupt3(BIT_TRAIN_IDLE_PERIOD, NUMBER_OF_BITS, !ON_RISING);
    } else {
      is_startInterrupt3(BIT_TRAIN_IDLE_PERIOD, NUMBER_OF_BITS, ON_RISING);
    }
    delay(10);
  } else {
    delay(10);
  }  
}

