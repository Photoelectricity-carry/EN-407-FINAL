#include "tim.h"
#include "tsc2300.h"
// #include "hal_flash.h"
#include "stm32f4xx.h" // Device header
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal.h"

// float R=0,G=0,B=0;
uint16_t Rgena, Ggena, Bgena;
uint16_t Ramount, Gamount, Bamount;
uint16_t amount = 0;
uint16_t d[3];
uint16_t s;
uint16_t y;
uint8_t red_flag;
uint8_t white_flag = 0;
uint16_t x[3];
// ��ǰʵ�ز��Զ���ƽ������x[3]���������ֵ
// uint16_t r_t=62,g_t=65,b_t=75;
uint16_t r_t = 92, g_t = 96, b_t = 103;
EXTI_HandleTypeDef l;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_4)
	{
		amount++;
	}
}
// void tcs3200_init(u8 s0,u8 s1)
//{

//	GPIO_InitTypeDef	GPIO_InitStructure;
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PB�˿�ʱ��
//
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
////	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//������+��
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	S0=s0;
//	S1=s1;

//}
/*******************************************
 *
 *		  ��ƽ��
 *
 *******************************************/
void whitebalance(void)
{
	//	EXTIX_Init();	//�ⲿ�жϳ�ʼ��
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	//	S2=0;S3=0;//��ɫͨ��
	amount = 0; // ��ʼ����
	HAL_Delay(10);
	Rgena = amount; // �����ɫ����
	amount = 0;
	x[0] = Rgena;
	//	STMFLASH_Write(0x08004000,(u16*)x[0],1);
	//								 0x08000000
	//----------------------------------
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	//	S2=1;S3=1;//��ɫͨ��
	amount = 0;
	HAL_Delay(10);
	Ggena = amount; // �����ɫ����
	amount = 0;
	x[1] = Ggena;
	//	STMFLASH_Write(0x08004100,(u16*)x1[0],1);

	//---------------------------------
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	//	S2=0;S3=1;//��ɫͨ��
	amount = 0;
	HAL_Delay(10);
	Bgena = amount; // �����ɫ����
	amount = 0;
	x[2] = Bgena;
	//	STMFLASH_Write(0x08004000,(uint16_t*)x,3);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	//	S2=1;S3=0;//�ر�ͨ��
}

uint16_t tcs2300_RED(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	//	S2=0;S3=0;
	amount = 0;
	HAL_Delay(10);
	Ramount = (uint32_t)amount * 255 / r_t; // ȡRֵ
	if (Ramount > 255)
		Ramount = 255;
	return Ramount;
	//	amount=0;
}

uint16_t tcs2300_GREEN(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	//	S2=1;S3=1;
	amount = 0;
	HAL_Delay(10);
	Gamount = (uint32_t)amount * 255 / g_t; // ȡGֵ
	if (Gamount > 255)
		Gamount = 255;
	return Gamount;
	//	amount=0;
}

uint16_t tcs2300_BLUE(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	//	S2=0;S3=1;
	amount = 0;
	HAL_Delay(10);
	Bamount = (uint32_t)amount * 255 / b_t; // ȡBֵ
	if (Bamount > 255)
		Bamount = 255;
	return Bamount;
	//	amount=0;
}

uint16_t rgb(void) // һ�����Ƶ���ɫʶ����
{
	float H, L, R, G, B;
	float max, min;
	R = tcs2300_RED();
	G = tcs2300_GREEN();
	B = tcs2300_BLUE();

	// �������ֵ
	if (R == G && G == B)
		max = 1;
	else if (R >= G && R >= B)
		max = R;
	else if (G >= R && G >= B)
		max = G;
	else if (B >= G && B >= R)
		max = B;
	else
		max = 0;
	// ������Сֵ
	if (R == G && G == B)
		min = 1;
	else if (R <= G && R <= B)
		min = R;
	else if (G <= R && G <= B)
		min = G;
	else if (B <= G && B <= R)
		min = B;
	else
		min = 0;
	// ����ɫ��H
	if (max == R)
		H = 60 * ((G - B) / (max - min));
	if (max == G)
		H = 60 * ((B - R) / (max - min)) + 120;
	if (max == B)
		H = 60 * ((R - G) / (max - min)) + 240;
	if (max == min)
		H = 0;
	// ���HΪ������+360������Ϊ����
	if (H < 0)
		H += 360;
	// ��������L
	L = (max + min) / 2;

	if (R > 150 && G > 150 && B > 150) // ��ɫ
	{
		return 2;
	}
	else if (G > R && G > B && H < 200) // ��ɫ
	{
		return 1;
	}
	else if (R < 45 && G < 45 && B < 45) // ��ɫ
	{
		return 4;
	}
	else if (B > G && B > R) // ��ɫ
	{
		return 5;
	}
	else if (R > G && R > B) // ��ɫ
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

void tcs2300(int color_t) // ǰ����Ӧ��ɫ�ķ�·
{
	switch (color_t)
	{
	case 1:
		zuozhuan2();
		Tracking5();
		break;
	case 2:
		zuozhuan1();
		Tracking5();
		break;
	case 3:
		Tracking5();
		break;
	case 4:
		youzhuan1();
		Tracking5();
		break;
	case 5:
		youzhuan2();
		Tracking5();
		break;
	}
}
void tcs2300_turn(int color_t)
{
	switch (color_t)
	{
	case 1:
		youzhuan2();
		break;
	case 2:
		youzhuan1();
		break;
	case 3:
		break;
	case 4:
		zuozhuan1();
		break;
	case 5:
		zuozhuan2();
		break;
	}
}
