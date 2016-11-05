#ifndef MAIN_H_
#define MAIN_H_


#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_rcc.h"
#include "interrupt.h"

#define ORANGE 	GPIO_Pin_13
#define GREEN 	GPIO_Pin_12
#define RED 		GPIO_Pin_14
#define BLUE 		GPIO_Pin_15
#define BLUE_ON() GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define MODE_RED 0


void init_perif(void);//инициализация переферии


void init_perif(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOA, ENABLE);//включаем тактирование шины AHB1 на ней порты D и A
	GPIO_InitTypeDef GPIO_D, GPIO_A;// обьявляем структуру для инициализации портов
	//Устанавливаем режимы работы порта D
	GPIO_D.GPIO_Pin = GREEN|ORANGE|RED|BLUE;
	GPIO_D.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_D.GPIO_Speed = GPIO_Low_Speed;
	GPIO_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_D.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(GPIOD, &GPIO_D);// иницифлизируем сами порты
	
	//Устанавливаем режимы работы порта A
	GPIO_A.GPIO_Pin = GPIO_Pin_0;
	GPIO_A.GPIO_Mode = GPIO_Mode_IN;
	GPIO_A.GPIO_Speed = GPIO_Low_Speed;
	GPIO_A.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_A.GPIO_OType = GPIO_OType_OD;
	
	GPIO_Init(GPIOA, &GPIO_A);// иницифлизируем сами порты
	
}




#endif /*MAIN_H_*/








