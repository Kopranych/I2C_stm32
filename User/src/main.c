#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "interrupt.h"
#include "i2c.h"

int main()
{
	uint8_t data = 0;
	init_delay();
	init_perif();
	init_IT_i2c();
	I2C_init();
	while(1)
	{
		
		data = MPU_I2C_R(ACCEL_XOUT_L, MPU_6050_ADDRESS);
		data = MPU_I2C_R(GYRO_XOUT_L, MPU_6050_ADDRESS);
			
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
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
			
	}
	
	
}
