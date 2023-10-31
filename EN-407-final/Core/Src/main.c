/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
// DISC_Rotate(2150);				//1��ǰ
// DISC_Rotate(1025);				//1ʶ��
// DISC_Rotate(400);					//2��ǰ
// DISC_Rotate(1400);				//2ʶ��
// DISC_Rotate(900);					//3��ǰ
// DISC_Rotate(1800); 			  //3ʶ��
// DISC_Rotate(1350);				//4��ǰ
// DISC_Rotate(2200);				//4ʶ��
// DISC_Rotate(1750);	 			//5��ǰ
// DISC_Rotate(1000);				//5ʶ��
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Track.h"
#include "motor.h"
#include "duoji.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// fp32 feedback_1;
// fp32 feedback_2;
// fp32 set_speed_1;
// fp32 set_speed_2;

float H, L, R, G, B;
int color;
float max, min;
// pid_type_def motor[2];-
// const static fp32 motor_speed_pid[3] = {MOTOR_SPEED_PID_KP, MOTOR_SPEED_PID_KI, MOTOR_SPEED_PID_KD};
// const static fp32 motor_angle_pid[3] = {MOTOR_ANGLE_PID_KP,MOTOR_ANGLE_PID_KI, MOTOR_ANGLE_PID_KD};
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART6_UART_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM5_Init();
	MX_TIM6_Init();
	MX_TIM2_Init();
	MX_TIM9_Init();
	/* USER CODE BEGIN 2 */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART6_UART_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM5_Init();
	MX_TIM6_Init();
	MX_TIM2_Init();
	// ���������ʼ��pid
	// PID_init(&motor[0],PID_POSITION,motor_speed_pid,40, 100);
	// PID_init(&motor[1],PID_POSITION,motor_speed_pid,40, 100);

	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

	HAL_TIM_Base_Start_IT(&htim6);
	whitebalance();
	// ����ʼ
	/* USER CODE END WHILE */
	/*����1*/
	//PID��ʼ��
	Tracking_Init();
	// ��ʼ��ת�̺����צ��
	DISC_Rotate(2275); // 1��ǰ
	MG90S_Rotate_up1();
	MG90S_Rotate_up2();
	MG90S_Rotate_up3();
	MG90S_Rotate_up4();
	MG90S_Rotate_up5();

	Tracking();
	HAL_Delay(1000);
	MG90S_Rotate_down1(); // ���ץ
	HAL_Delay(1000);
	DISC_Rotate(600); // 2��ǰ
	Trackinghou();
	HAL_Delay(1000);
	Tracking2();
	HAL_Delay(1000);
	youzhuan2();
	HAL_Delay(1000);
	Tracking5();
	HAL_Delay(1000);
	MG90S_Rotate_down2(); // ���ץ
	HAL_Delay(1000);
	DISC_Rotate(1000); // 3��ǰ
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(1000);
	Tracking2();
	HAL_Delay(1000);
	zuozhuan3();
	HAL_Delay(2500);
	Tracking5();
	HAL_Delay(1000);
	MG90S_Rotate_down3();
	HAL_Delay(1000); // ���ץ
	Trackinghou();
	HAL_Delay(1000);
	Tracking2();
	HAL_Delay(1000);
	youzhuan2();
	// ���ʶ��
	// ��1
	DISC_Rotate(2225); // 1��ǰ
	HAL_Delay(500);
	DISC_Rotate(925); // 1��ɫ
	HAL_Delay(1000);
	color = rgb();
	DISC_Rotate(2225); // 1��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up1();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��2
	DISC_Rotate(600); // 2��ǰ
	HAL_Delay(500);
	DISC_Rotate(1325); // 2��ɫ
	HAL_Delay(1000);
	color = rgb();
	DISC_Rotate(600); // 2��ǰ
	HAL_Delay(100);
	tcs2300(color);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up2();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��3
	DISC_Rotate(1000); // 3��ǰ
	HAL_Delay(500);
	DISC_Rotate(1350); // 3����
	HAL_Delay(500);
	DISC_Rotate(1800); // 3��ɫ
	HAL_Delay(1000);
	color = rgb();
	DISC_Rotate(1350); // 3����
	HAL_Delay(500);
	DISC_Rotate(1000); // 3��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up3();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	DISC_Rotate(2150); // 1��ǰ
	/*����2*/
	// F��
	zuozhuan2_3();
	HAL_Delay(500);
	zuozhuan1_3();
	HAL_Delay(500);
	Tracking6();
	HAL_Delay(500);
	Tracking7();
	HAL_Delay(500);
	MG90S_Rotate_down1();
	MG90S_Rotate_down2();
	MG90S_Rotate_down3();
	MG90S_Rotate_down4();
	MG90S_Rotate_down5();
	HAL_Delay(2500);
	Trackinghou3();
	HAL_Delay(100);
	Tracking2();
	HAL_Delay(100);
	youzhuan1_3();
	HAL_Delay(1000);
	youzhuan2_3();
	HAL_Delay(1000);
	// ��ת���ʶ��ǰ������
	// ��4
	DISC_Rotate(2150); // 4��ɫ
	HAL_Delay(1000);
	color = rgb();
	DISC_Rotate(1750); // 4����
	HAL_Delay(500);
	DISC_Rotate(1400); // 4��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up4();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��5
	DISC_Rotate(1850); // 5��ǰ
	HAL_Delay(1500);
	DISC_Rotate(2150); // 5����
	HAL_Delay(1500);
	DISC_Rotate(525); // 5��ɫ
	HAL_Delay(1000);
	color = rgb();
	DISC_Rotate(2150); // 5����
	HAL_Delay(500);
	DISC_Rotate(1850); // 5��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up5();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��1
	DISC_Rotate(2225); // 1��ǰ
	HAL_Delay(1500);
	DISC_Rotate(925); // 1��ɫ
	HAL_Delay(1500);
	color = rgb();
	DISC_Rotate(2225); // 1��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up1();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��2
	DISC_Rotate(600); // 2��ǰ
	HAL_Delay(1500);
	DISC_Rotate(1325); // 2����
	HAL_Delay(500);
	DISC_Rotate(1325); // 2��ɫ
	HAL_Delay(1500);
	color = rgb();
	DISC_Rotate(900); // 2����
	HAL_Delay(500);
	DISC_Rotate(600); // 2��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up2();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��3
	DISC_Rotate(1000); // 3��ǰ
	HAL_Delay(1500);
	DISC_Rotate(1350); // 3����
	HAL_Delay(1500);
	DISC_Rotate(1800); // 3��ɫ
	HAL_Delay(1500);
	color = rgb();
	DISC_Rotate(1350); // 3����
	HAL_Delay(500);
	DISC_Rotate(1000); // 3��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up3();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	DISC_Rotate(500); // 1����
	HAL_Delay(500);
	DISC_Rotate(2225); // 1��ǰ
	// G��
	youzhuan2();
	HAL_Delay(1000);
	youzhuan1();
	HAL_Delay(1000);
	Tracking6();
	Tracking7();
	HAL_Delay(100);
	MG90S_Rotate_down1();
	MG90S_Rotate_down2();
	MG90S_Rotate_down3();
	MG90S_Rotate_down4();
	MG90S_Rotate_down5();
	HAL_Delay(2500);
	Trackinghou3();
	HAL_Delay(100);
	Tracking2();
	HAL_Delay(100);
	zuozhuan1();
	zuozhuan2();
	HAL_Delay(1000);
	// ��ת���ʶ��ǰ������
	// ��4
	DISC_Rotate(2150); // 4��ɫ
	HAL_Delay(1000);
	color = rgb();
	DISC_Rotate(1750); // 4����
	HAL_Delay(500);
	DISC_Rotate(1400); // 4��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up4();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��5
	DISC_Rotate(1850); // 5��ǰ
	HAL_Delay(1500);
	DISC_Rotate(2150); // 5����
	HAL_Delay(1500);
	DISC_Rotate(525); // 5��ɫ
	HAL_Delay(1000);
	color = rgb();
	DISC_Rotate(2150); // 5����
	HAL_Delay(500);
	DISC_Rotate(1850); // 5��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up5();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��1
	DISC_Rotate(2225); // 1��ǰ
	HAL_Delay(1500);
	DISC_Rotate(925); // 1��ɫ
	HAL_Delay(1500);
	color = rgb();
	DISC_Rotate(2225); // 1��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up1();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��2
	DISC_Rotate(600); // 2��ǰ
	HAL_Delay(1500);
	DISC_Rotate(900); // 2����
	HAL_Delay(500);
	DISC_Rotate(1325); // 2��ɫ
	HAL_Delay(1500);
	color = rgb();
	DISC_Rotate(900); // 2����
	HAL_Delay(500);
	DISC_Rotate(600); // 2��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up2();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	HAL_Delay(1000);
	// ��3
	DISC_Rotate(1000); // 3��ǰ
	HAL_Delay(1500);
	DISC_Rotate(1350); // 3����
	HAL_Delay(1500);
	DISC_Rotate(1800); // 3��ɫ
	HAL_Delay(1500);
	color = rgb();
	DISC_Rotate(1350); // 3����
	HAL_Delay(500);
	DISC_Rotate(1000); // 3��ǰ
	HAL_Delay(100);
	tcs2300(color);
	HAL_Delay(100);
	Tracking3();
	HAL_Delay(100);
	MG90S_Rotate_up3();
	HAL_Delay(1000);
	Trackinghou();
	HAL_Delay(500);
	Tracking2();
	HAL_Delay(500);
	tcs2300_turn(color);
	DISC_Rotate(500); // 1����
	HAL_Delay(500);
	DISC_Rotate(2225); // 1��ǰ
	// ��λ
	Trackinghou2();
	// �������

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		//	R=tcs2300_RED();
		//	G=tcs2300_GREEN();
		//	B=tcs2300_BLUE();
		//
		//	//�������ֵ
		//	if(R==G&&G==B)	max = 1;
		//	else if(R>=G&&R>=B)	max = R;
		//	else if(G>=R&&G>=B)	max = G;
		//	else if(B>=G&&B>=R)	max = B;
		//	else	max = 0;
		//	//������Сֵ
		//	if(R==G&&G==B)	min = 1;
		//	else if(R<=G&&R<=B)	min = R;
		//	else if(G<=R&&G<=B)	min = G;
		//	else if(B<=G&&B<=R)	min = B;
		//	else	min = 0;
		//	//����ɫ��H
		//	if(max==R)	H = 60*((G-B)/(max-min));
		//	if(max==G)	H = 60*((B-R)/(max-min))+120;
		//	if(max==B)	H = 60*((R-G)/(max-min))+240;
		//	if(max==min)	H = 0;
		//	//���HΪ������+360������Ϊ����
		//	if(H<0)	H+=360;
		//	//��������L
		//	L =(max+min)/2;
		//
		//	if(R>200 && G>200 && B>200)//��ɫ
		//	{
		//		color = 2;
		//	}
		//		else if(G>R && G>B && H<200)//��ɫ
		//	{
		//		color = 1;
		//	}
		//	else if(R<50 && G<50 && B<50)//��ɫ
		//	{
		//		color = 4;
		//	}
		//	else if(B>G && B>R && H>200)//��ɫ
		//	{
		//		color = 5;
		//	}
		//	else if(R>G && R>B)//��ɫ
		//	{
		//		color = 3;
		//	}
		//   else
		//	{
		//		color = 0;
		//	}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 72;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
