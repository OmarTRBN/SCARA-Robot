// timers.h

#include "stm32f4xx.h"                  // Device header

void setTim4Frequency(uint16_t psc, uint16_t arr);

void initTim4Ch1();
void startTim4Ch1();
void stopTim4Ch1();