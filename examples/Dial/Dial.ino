#include "InterruptSampler.h"

static const float CONVERT_TO_MM = 0.01;
static const float CONVERT_TO_INCH = 0.0005;
static const uint32_t BIT_TRAIN_IDLE_PERIOD = 100000;
 
void setup()
{
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  
  Serial.begin(9600);
  is_startInterrupt3(BIT_TRAIN_IDLE_PERIOD, 24, true);
}

float adjustForCaliper(uint32_t val, bool* isMM) {
  int32_t adjusted = val;
  
  // bit 22 signals imperical value
  if(adjusted & bit(22) ) { 
     *isMM = false;
     // lower bit 22 again
     adjusted &= ~bit(22);  
   } else {
    *isMM = true;
   }
  
   // bit 20 signals negative value  
   if (adjusted & bit(20) ) {
     adjusted &= ~bit(20); // lower bit 20 again
     adjusted = -adjusted; // set it to negative value
   }
   //is_printBinary32(adjusted); 
   //Serial.println(); 
   if (*isMM) {
     return CONVERT_TO_MM*adjusted;
   } else {
     return CONVERT_TO_INCH*adjusted;
   }
}

void printResult() {
  uint32_t res = is_assembleResult(1,23);
  bool isMM = true;
  float result = adjustForCaliper(res, &isMM);
  Serial.print("Result: ");
  Serial.print(" ");
  is_printBinary32(res);
  Serial.print(" ");
  if (isMM){
    Serial.print(result,2); Serial.print("mm"); 
  } else {
    Serial.print(result,4); Serial.print("\"");
  } 
  Serial.print(" currbit="); Serial.println(is_currentBit);
}

void loop()
{  
   if (is_isDone()) {  
     delay(10);
     printResult();
     delay(1000);
     is_startInterrupt3(BIT_TRAIN_IDLE_PERIOD, 24, true);
     delay(10);
   } else {
     delay(10);
   }  
}

