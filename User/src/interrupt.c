
#include "interrupt.h"
//-----------------------------------------------------------------------------------
//��������� ��������� ��������
enum measure_MPU
{
		accel_xh,
		accel_xl,
		accel_yh,
		accel_yl,
		accel_zh,
		accel_zl,
		hyro_xh,
		hyro_xl,
		hyro_yh,
		hyro_yl,
		hyro_zh,
		hyro_zl,
		temperature_h,
		temperatyre_l
};

uint8_t array_adress[] =//������ ��������� ������ MPU6050
	{ ACCEL_XOUT_H, ACCEL_XOUT_L, ACCEL_YOUT_H, ACCEL_YOUT_L, ACCEL_ZOUT_H, ACCEL_ZOUT_L, 
	GYRO_XOUT_H, GYRO_XOUT_L, GYRO_YOUT_H, GYRO_YOUT_L, GYRO_ZOUT_H, GYRO_ZOUT_L,
			TEMP_OUT_H, TEMP_OUT_L };
	enum measure_MPU current = accel_xh;//������ ���� �� ������� ��������
/*----------------------------------------------------------------------------------------------------
 ��������� ������� ���������� SysTick
*/
uint16_t delay_count = 0;

void init_delay(void)
{
	SysTick_Config(SystemCoreClock/1000);//������������� SysTick ������ ���������� ��� � 1/1000 ���.
}


void SysTick_Handler(void)// ������ ����������
{
	if(delay_count>0)
		delay_count--;
}

void delay_ms(uint16_t delay_temp) // ������� �������� ������������� ����������� ���������� SysTick
{
	delay_count = delay_temp;
	while(delay_count);
}
/*----------------------------------------------------------------------------------------------------
 ��������� ������� ���������� i2c
*/
void init_IT_i2c(void)
{
	I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE);//�������� ���������� �� �������
	I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE);//�������� ���������� �� ������
}
void I2C1_EV_IRQHandler(void)
{
		uint16_t status_evt = get_status();
}
void I2C1_ER_IRQHandler(void)
{
		uint16_t status_err = get_status();
}
