

#include "i2c.h"
#include "stm32f4xx.h"

void I2C_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//��������� ���� ��� i2c
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);//��������� ��� i2c
	//--------------------------------------------
	GPIO_InitTypeDef busi2c;//������� ��������� 
	I2C_InitTypeDef i2c;//��� �������������
	//------------------------------------
	i2c.I2C_ClockSpeed = 100000;//100kHz
	i2c.I2C_Mode = I2C_Mode_I2C;
  i2c.I2C_DutyCycle = I2C_DutyCycle_2;
  i2c.I2C_OwnAddress1 = OWNADRESS;
  i2c.I2C_Ack = I2C_Ack_Disable;
  i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_Init(I2C1, &i2c);
	//---------------------------------------
	busi2c.GPIO_Pin = BUS_SCL|BUS_SDA;
	busi2c.GPIO_Mode = GPIO_Mode_AF;
	busi2c.GPIO_Speed = GPIO_Speed_2MHz;
	busi2c.GPIO_OType = GPIO_OType_OD;
	busi2c.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &busi2c);
	//---------------------------------------------
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);//�������� �������������� 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);//������� �����
	//----------------------------------------------
	I2C_Cmd(I2C1, ENABLE);//�������� ������ i2c
	
	MPU_I2C_W(MPU_6050_ADDRESS_W,PWR_MGMT_1, 0x00);//�������� ������� ���������� ��������, ��� ����� �� �������� ������
}


void I2C_start(void)
{
	I2C_GenerateSTART(I2C1, ENABLE);//���������� �����
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//���� ������� �����
}


void I2C_stop(void)
{
	I2C_GenerateSTOP(I2C1, ENABLE);
}



void i2c_send_adress(uint8_t Address, uint8_t I2C_Direction)
{
	I2C_Send7bitAddress(I2C1, Address, I2C_Direction);
	if(I2C_Direction)
	{
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
	else
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
}

void I2C_tranciv_byte(uint8_t byte)
{
	I2C_SendData(I2C1, byte);//���������� ����
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//���� ���� ������ ����������
}


uint8_t I2C_receiver_byte(void)
{
		uint8_t data;
    while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));//���� ������ ������
    data = I2C_ReceiveData(I2C1);// ��������� ������
    return data;
}


uint8_t I2C_receiver_last_byte(void)
{
		uint8_t data;
    while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) );//���� ������ ������
    data = I2C_ReceiveData(I2C1);// ��������� ������
    return data;
}

uint32_t get_status(void)
{
	uint32_t status = I2C_GetLastEvent(I2C2);//���������� �������� ��������� ��������� sr2<<16|sr1
	return status;
}

uint8_t MPU_I2C_R(uint8_t ra, uint8_t addrr)
{
	uint8_t data;
	I2C_start();//���������� ������� �����
	i2c_send_adress(addrr, I2C_Direction_Transmitter);//���������� ����� ������ �� ������
	I2C_tranciv_byte(ra);//���������� ����� �������� ������ ����� ������ ������
	I2C_start();//���������� ��������� �����
	i2c_send_adress(addrr, I2C_Direction_Receiver);//���������� ����� ������ �� ������
	data = I2C_receiver_last_byte();//������ ������ �� ��������
	I2C_stop();//���������� ������� ����
	return data;
}

void MPU_I2C_W(uint8_t addrw, uint8_t ra, uint8_t data)
{
	I2C_start();//���������� ������� �����
	i2c_send_adress(addrw, I2C_Direction_Transmitter);//���������� ����� ������ �� ������
	I2C_tranciv_byte(ra);//���������� ����� �������� ���� ����� ���������� ������
	I2C_tranciv_byte(data);//���������� ������
	I2C_stop();//���������� ������� ����
}


