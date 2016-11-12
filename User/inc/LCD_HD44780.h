// Библиотека для работы с LCD HD44780 диспоеем
/*
+---------------------------------------------------------------+
| File    	     : LCD_HD44780.h                                |
| Author  	 	   : Kopranych                                    |
| Git repository : github.com/Kopranych/LCD_HD44780_to_stm32_lib|
| Mail   			   : kopranych@gmail.ru                           |
| Data    	     : 04/11/2016                                   |
| Device   		   : STM32F4xx                                    |
| Compiler 		   : MDK-ARM (Keil)                               |
| Project  		   : LCD_44780                                    |
| Version  	   	 : 1.0  							            			        |
| Discription 	 : Library for working with LCD HD44780         |
+---------------------------------------------------------------+
*/
#ifndef LCD_HD44780_H_
#define LCD_HD44780_H_

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_rcc.h"
#include "interrupt.h"
#include <stdio.h>
#include <stdlib.h>


////////////////////////переопределения////////////////////////////////////////
//#define F_CPU 8000000L
#define PORT_SIG 	  GPIOA//порт управления
//#define DDR_SIG	      DDRB//
//#define PIN_SIG   	  PINB//
#define RS  	      GPIO_Pin_0//1 передаем данные, 0 передаем команду
#define E      	      GPIO_Pin_1//строб
//#define RW	   	   	  PB1//направление:1 чтение дисплея, 0 запись в дисплей
#define DB4					GPIO_Pin_2
#define DB5		 			GPIO_Pin_3
#define DB6					GPIO_Pin_4
#define DB7					GPIO_Pin_5
#define PORT_DATA	  PORT_SIG//порт данных
//#define DDR_DATA	  DDRA//
//#define PIN_DATA	  PINA//
//#define BF       	  PA7//флаг занятости если 1 то занят дисплей если 0 то свободен
#define RS_COM   	  0//передаем команду
#define RS_DATA  	  1//передаем данные
#define ON			  1//включение 
#define OFF			  0//выключение
#define BUS_LINE	  0x28//2 линии данных, 4 бита шина
#define BUS_LINE1	  0x20//1 линии данных, 4 бита шина
#define SEC_LINE	  0xA8//Вторая линия первый символ
#define FIRS_LINE 	  0x80//Первая линия первый символ
#define FIRST		  0x80//Адрес первой ячейки 
#define THIRD		  0x82//
#define FOURTH		  0x83//Адрес четвертой ячейки	  
#define SEVENTH		  0x86//Адрес седьмой ячейки
#define EIGHTH		  0x87//
#define ELEVENTH	  0x8B//
#define THIRTEENTH 	  0x8C//
#define THIRD_S	      0xC2//
#define SEVENTH_S	  0xC6//
#define EIGHTH_S	  0xC8//
#define ELEVENTH_S 	  0xB2//
#define THIRTEENTH_S  0xCD//
#define FIFTEENTH_S   0xB6//
#define MASK_DATA 		0xFFC3
#define MASK_LOW			0x00F0
#define MASK_HIGH			0x000F

//////////////////////////////////////функции///////////////////////////////
void LCD_init_pin(void);//инициализация портов для дисплея
void LCD_init(void);//функция инициализации дисплея 
void LCD_write(uint16_t data, uint16_t BIT_RS);//функция записи в дисплей
void LCD_read_BF(void);//функция чтения флага BF готовности из дисплея на данном железе НЕ РАБОТАЕТ!!!делаем через delay)))
void LCD_write_adress(uint16_t data, uint16_t adress);//функция записи в дисплей по конкретному адресу
void LCD_write_str(int8_t *string);//запись строки на дисплей
void line_wrapping(int8_t number);//переключение на нужную строку
void clean_display(void);//очистка дисплея
void kursor_adress(uint8_t adress);//установка курсора на нужный адрес
//void LCD_alignment(int16_t str, uint8_t adress);// функция выравнивания на дисплее значений
void my_itoa(int value, char* buf, int base);// конвертируем число в строку

#endif
