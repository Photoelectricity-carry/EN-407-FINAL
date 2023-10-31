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
// 赛前实地测试读白平衡数组x[3]填好这三个值
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
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB端口时钟
//
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
////	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输+出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	S0=s0;
//	S1=s1;

//}
/*******************************************
 *
 *		  白平衡
 *
 *******************************************/
void whitebalance(void)
{
	//	EXTIX_Init();	//外部中断初始化
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	//	S2=0;S3=0;//红色通道
	amount = 0; // 开始计数
	HAL_Delay(10);
	Rgena = amount; // 求出红色因子
	amount = 0;
	x[0] = Rgena;
	//	STMFLASH_Write(0x08004000,(u16*)x[0],1);
	//								 0x08000000
	//----------------------------------
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	//	S2=1;S3=1;//绿色通道
	amount = 0;
	HAL_Delay(10);
	Ggena = amount; // 求出绿色因子
	amount = 0;
	x[1] = Ggena;
	//	STMFLASH_Write(0x08004100,(u16*)x1[0],1);

	//---------------------------------
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	//	S2=0;S3=1;//蓝色通道
	amount = 0;
	HAL_Delay(10);
	Bgena = amount; // 求出蓝色因子
	amount = 0;
	x[2] = Bgena;
	//	STMFLASH_Write(0x08004000,(uint16_t*)x,3);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	//	S2=1;S3=0;//关闭通道
}

uint16_t tcs2300_RED(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	//	S2=0;S3=0;
	amount = 0;
	HAL_Delay(10);
	Ramount = (uint32_t)amount * 255 / r_t; // 取R值
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
	Gamount = (uint32_t)amount * 255 / g_t; // 取G值
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
	Bamount = (uint32_t)amount * 255 / b_t; // 取B值
	if (Bamount > 255)
		Bamount = 255;
	return Bamount;
	//	amount=0;
}

uint16_t rgb(void) // 一个完善的颜色识别函数
{
	float H, L, R, G, B;
	float max, min;
	R = tcs2300_RED();
	G = tcs2300_GREEN();
	B = tcs2300_BLUE();

	// 计算最大值
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
	// 计算最小值
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
	// 计算色相H
	if (max == R)
		H = 60 * ((G - B) / (max - min));
	if (max == G)
		H = 60 * ((B - R) / (max - min)) + 120;
	if (max == B)
		H = 60 * ((R - G) / (max - min)) + 240;
	if (max == min)
		H = 0;
	// 如果H为负，则+360，修正为正数
	if (H < 0)
		H += 360;
	// 计算亮度L
	L = (max + min) / 2;

	if (R > 150 && G > 150 && B > 150) // 白色
	{
		return 2;
	}
	else if (G > R && G > B && H < 200) // 绿色
	{
		return 1;
	}
	else if (R < 45 && G < 45 && B < 45) // 黑色
	{
		return 4;
	}
	else if (B > G && B > R) // 蓝色
	{
		return 5;
	}
	else if (R > G && R > B) // 红色
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

void tcs2300(int color_t) // 前往对应颜色的分路
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
