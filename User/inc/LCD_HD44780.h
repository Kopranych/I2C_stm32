// ���������� ��� ������ � LCD HD44780 ��������
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


////////////////////////���������������////////////////////////////////////////
//#define F_CPU 8000000L
#define PORT_SIG 	  GPIOA//���� ����������
//#define DDR_SIG	      DDRB//
//#define PIN_SIG   	  PINB//
#define RS  	      GPIO_Pin_0//1 �������� ������, 0 �������� �������
#define E      	      GPIO_Pin_1//�����
//#define RW	   	   	  PB1//�����������:1 ������ �������, 0 ������ � �������
#define DB4					GPIO_Pin_2
#define DB5		 			GPIO_Pin_3
#define DB6					GPIO_Pin_4
#define DB7					GPIO_Pin_5
#define PORT_DATA	  PORT_SIG//���� ������
//#define DDR_DATA	  DDRA//
//#define PIN_DATA	  PINA//
//#define BF       	  PA7//���� ��������� ���� 1 �� ����� ������� ���� 0 �� ��������
#define RS_COM   	  0//�������� �������
#define RS_DATA  	  1//�������� ������
#define ON			  1//��������� 
#define OFF			  0//����������
#define BUS_LINE	  0x28//2 ����� ������, 4 ���� ����
#define BUS_LINE1	  0x20//1 ����� ������, 4 ���� ����
#define SEC_LINE	  0xA8//������ ����� ������ ������
#define FIRS_LINE 	  0x80//������ ����� ������ ������
#define FIRST		  0x80//����� ������ ������ 
#define THIRD		  0x82//
#define FOURTH		  0x83//����� ��������� ������	  
#define SEVENTH		  0x86//����� ������� ������
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

//////////////////////////////////////�������///////////////////////////////
void LCD_init_pin(void);//������������� ������ ��� �������
void LCD_init(void);//������� ������������� ������� 
void LCD_write(uint16_t data, uint16_t BIT_RS);//������� ������ � �������
void LCD_read_BF(void);//������� ������ ����� BF ���������� �� ������� �� ������ ������ �� ��������!!!������ ����� delay)))
void LCD_write_adress(uint16_t data, uint16_t adress);//������� ������ � ������� �� ����������� ������
void LCD_write_str(int8_t *string);//������ ������ �� �������
void line_wrapping(int8_t number);//������������ �� ������ ������
void clean_display(void);//������� �������
void kursor_adress(uint8_t adress);//��������� ������� �� ������ �����
//void LCD_alignment(int16_t str, uint8_t adress);// ������� ������������ �� ������� ��������
void my_itoa(int value, char* buf, int base);// ������������ ����� � ������

#endif
