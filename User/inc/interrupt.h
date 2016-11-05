#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#include "stm32f4xx.h"                  // Device header
#include "i2c.h"



void init_delay(void);
void delay_ms(uint16_t delay_temp); // функция задержки реализованная посредством прерываний SysTick
void SysTick_Handler(void);// вектор прерывания
//---------------------------------------------------------------------------------------
void init_IT_i2c(void);

#endif /*INTERRUPT_H_*/
