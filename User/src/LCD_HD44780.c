// Библиотека для работы с LCD HD44780 диспоеем


#include "LCD_HD44780.h"
#include "stm32f4xx.h"    
#include <stdlib.h>



void LCD_init_pin(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE);//включаем тактирование шины AHB1 на ней порты D и A
	GPIO_InitTypeDef PORT_LCD;// обьявляем структуру для инициализации портов

	//Устанавливаем режимы работы порта C
	PORT_LCD.GPIO_Pin = RS|E|DB4|DB5|DB6|DB7;
	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;
	PORT_LCD.GPIO_Speed = GPIO_Low_Speed;
	PORT_LCD.GPIO_PuPd = GPIO_PuPd_NOPULL;
	PORT_LCD.GPIO_OType = GPIO_OType_OD;
	
	GPIO_Init(GPIOA, &PORT_LCD);// инициализируем сами порты

	
	GPIO_InitTypeDef GPIO_D;// обьявляем структуру для инициализации портов
	//Устанавливаем режимы работы порта D
	GPIO_D.GPIO_Pin = GPIO_Pin_13;
	GPIO_D.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_D.GPIO_Speed = GPIO_Low_Speed;
	GPIO_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_D.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(GPIOD, &GPIO_D);// иницифлизируем сами порты
	
	

	
}


/////////////////////////////////////////
void LCD_init(void)
{	
	delay_ms(40);//
//	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;//порты на //выход//управляющие порты //на выход
	//PORT_SIG &= ~(ON<<RW);//порт чтения/записи  на запись
	delay_ms(40);
	LCD_write(BUS_LINE,RS_COM);//2 линии данных, 4 бита шина
	LCD_write(BUS_LINE,RS_COM);
	LCD_write(BUS_LINE,RS_COM);
	LCD_write(BUS_LINE,RS_COM);
	LCD_write(0x01,RS_COM);//очистка экрана
	LCD_write(0x06,RS_COM);//инкремент адреса экран не движется
	
	LCD_write(0x0C,RS_COM);//включить дисплей

}

void LCD_write(uint16_t data, uint16_t BIT_RS)
{
	delay_ms(40);
//	LCD_read_BF();
//	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;//на выход
//	PORT_SIG &= ~(ON<<RW);
	if(BIT_RS == RS_COM)// если 0  
	{
		GPIO_ResetBits(PORT_SIG, RS);//то Команда
	} 
	else GPIO_SetBits(PORT_SIG, RS);// иначе 1 то данные 
	uint16_t tmp = data;//сохронили данные во временном
	
	uint16_t temp = GPIO_ReadInputData(PORT_DATA) & MASK_DATA;// очистили пины PB5,PB6,PB7,PB8 для записи туда данных
	temp |= (data &MASK_LOW)>>2;// обрезали младщую тетраду данных 
	GPIO_Write(PORT_DATA, temp);//выствали тетраду в порт
	GPIO_SetBits(PORT_SIG, E);//строб вверх
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//строб вниз старшая тетрада на дисплей 
	temp = GPIO_ReadInputData(PORT_DATA) & MASK_DATA;// очистили пины PB5,PB6,PB7,PB8 для записи туда данныхх
	temp|= (tmp & MASK_HIGH)<<2;// обрезали старшую тетраду
	GPIO_Write(PORT_DATA, temp);//выставили младшую тетраду в порт
	GPIO_SetBits(PORT_SIG, E);//строб вверх
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//строб вниз старшая тетрада на дисплей 
//	_delay_ms(40);	

}

void LCD_write_adress(uint16_t data, uint16_t adress)
{
	delay_ms(40);
//	LCD_read_BF();
	LCD_write(adress, RS_COM);
//	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;//на выход
//	PORT_SIG &= ~(ON<<RW);
	GPIO_SetBits(PORT_SIG, RS);// иначе 1 то данные 
	uint16_t tmp = data;//сохронили данные во временном
	uint16_t temp = GPIO_ReadInputData(PORT_DATA) & MASK_DATA;// очистили пины PB5,PB6,PB7,PB8 для записи туда данных
	temp |= (data &MASK_LOW)>>2;// обрезали младщую тетраду данных  
	GPIO_Write(PORT_DATA, temp);//выствали тетраду в порт
	GPIO_SetBits(PORT_SIG, E);//строб вверх
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//строб вниз старшая тетрада на дисплей 
	temp = GPIO_ReadInputData(PORT_DATA) & MASK_DATA;// очистили пины PB5,PB6,PB7,PB8 для записи туда данных
	temp|= (tmp & MASK_HIGH)<<2;// обрезали старшую тетраду
	GPIO_Write(PORT_DATA, temp);//выставили младшую тетраду в порт
	GPIO_SetBits(PORT_SIG, E);//строб вверх
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//строб вниз старшая тетрада на дисплей 
	delay_ms(40);	
}

void LCD_write_str(int8_t *string)
{
	while(*string)
	{
		LCD_write(*string,RS_DATA);
		string++;
	}
}

void line_wrapping(int8_t number)
{
	if(number == 1)
	{
	 LCD_write(FIRS_LINE,RS_COM); 
	}
	else
	 LCD_write(SEC_LINE,RS_COM);	
}

void clean_display(void)
{
	LCD_write(0x01,RS_COM);
}

void kursor_adress(uint8_t adress)
{
		LCD_write(adress, RS_COM);
}

/*inline void LCD_alignment(int16_t str, uint8_t adress)
{	
	uint16_t buffer[] = {' ',' ',' ',' '};
	uint16_t buffer1[] = {' ',' ',' ',' ',' '};
	itoa(str, buffer, 10);

	if (str < 0)
		{
			if (str > (-10))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str(buffer1);
			}
			else if (str > (-100))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("    ");
			}
			else if (str  >(-1000))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
			else if (str  <=(-1000))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
		}

		else
		{
			if (str < 10)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("     ");
			}
			else if (str < 100)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("    ");
			}
			else if (str < 1000)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
			else if (str >= 1000)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
		}
}


void LCD_read_BF()
{
	uint8_t tmp = 0;
	uint8_t data = 0;

	DDR_DATA &= 0x0F;
	PORT_DATA |= 0xF0;
	PORT_SIG |= (ON<<RW);
	PORT_SIG &= ~(ON<<RS);
	
	do{
	PORT_SIG|= (ON<<E);
	_delay_ms(10);
	data = PIN_DATA & 0xF0;
	PORT_SIG &= ~(ON<<E);
	
	tmp = data;
	PORT_SIG|= (ON<<E);
	_delay_ms(10);
	data = PIN_DATA & 0xF0;
	PORT_SIG &= ~(ON<<E);
	
	data = data>>4;
	tmp|=data;
	}while((tmp &(1<<BF))!=0);		
}
*/

void my_itoa(int value, char* buf, int base)
	{
	
	int i = 30;
	
	buf = "";
	
	for(; value && i ; --i, value /= base) buf = "0123456789abcdef"[value % base] + buf;
	
}


