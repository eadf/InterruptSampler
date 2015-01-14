#ifndef INTERRUPT_SAMPLER_INCLUDE
#define INTERRUPT_SAMPLER_INCLUDE
#include <stdint.h>


#define IS_BUFFER_SIZE 512
extern volatile uint32_t is_now;
extern volatile uint32_t is_period;
extern volatile uint8_t is_bit3Sample;
extern volatile uint32_t is_minPeriod;
extern volatile uint32_t is_maxPeriod;
extern volatile uint16_t is_currentBit;
extern volatile uint8_t is_bitBuffer[IS_BUFFER_SIZE]; // 4095 bits sample buffer
extern volatile uint32_t is_minIdlePeriod;

void is_startInterrupt1(bool onRising);
void is_startInterrupt2(uint32_t endOfBlockPeriod, bool onRising);
void is_startInterrupt3(uint32_t endOfBlockPeriod, uint16_t bitsToLookFor, bool onRising);
void is_stopInterrupt(void);

void is_printState(void);
bool is_isDone(void);

/**
 * assembles a uint32_t from the sampled result.
 * fromBit and toBit are inclusive and start from bit 0.
 * e.g. is_assembleResult(0,1, true) will look at two bits.
 * The duplicateHighBit parameter defines how the 'overflow' bits should be handled.
 */
uint32_t is_assembleResult(int fromBit, int toBit, bool duplicateHighBit);

void is_printBuffer(uint16_t untilBit);
void is_printBinary8(uint8_t data);
void is_printBinary16(uint16_t data);
void is_printBinary32(uint32_t data);

void is_printSampleStatistics(void);

#endif
