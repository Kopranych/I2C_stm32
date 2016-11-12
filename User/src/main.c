#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "interrupt.h"
#include "i2c.h"
#include "LCD_HD44780.h"


int main()
{
	uint8_t data_ax = 0;
	uint8_t data_gx = 0;
	int8_t buf_ax[2], buf_gx[2];
	init_delay();
	init_perif();
	LCD_init_pin();
	LCD_init();
	init_IT_i2c();
	I2C_init();
	kursor_adress(SEC_LINE);
	LCD_write_str("Lets go");
	while(1)
	{
		
		data_ax = MPU_I2C_R(ACCEL_XOUT_H, MPU_6050_ADDRESS);
		data_gx = MPU_I2C_R(GYRO_XOUT_H, MPU_6050_ADDRESS);
		sprintf(buf_ax, "%u",data_ax);	
		sprintf(buf_gx, "%u",data_gx);
		LCD_write_adress(FIRS_LINE, RS_COM);
		LCD_write_str(buf_ax);
		kursor_adress(SEC_LINE);
		LCD_write_str(buf_gx);
		
/*		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			GPIO_ResetBits(GPIOD, GREEN);
			GPIO_SetBits(GPIOD, ORANGE);
			delay_ms(1000);
			GPIO_ResetBits(GPIOD, ORANGE);
			GPIO_SetBits(GPIOD, RED);
			delay_ms(1000);
			GPIO_ResetBits(GPIOD, RED);
			BLUE_ON();
			delay_ms(1000);
			GPIO_ResetBits(GPIOD, BLUE);
		}
		else
			{
				GPIO_ResetBits(GPIOD, ORANGE);
				GPIO_SetBits(GPIOD, GREEN);
			}
*/			
	}
	
	
}
