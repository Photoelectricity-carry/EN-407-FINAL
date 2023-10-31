#include "Track.h"
#include "main.h"
#include "motor.h"
#include "pid.h"
#include "tim.h"

extern TIM_HandleTypeDef htim6;
int16_t speed, speed1, speed2;
int angle1, angle2;
int16_t feedback_1;
int16_t feedback_2;
int16_t you_set_speed_1;
int16_t zuo_set_speed_2;
int flag_ = 0;
float flag[14];

pid_type_def motor[2];
const static fp32 motor_speed1_pid[3] = {MOTOR_SPEED1_PID_KP, MOTOR_SPEED1_PID_KI, MOTOR_SPEED1_PID_KD};
const static fp32 motor_speed2_pid[3] = {MOTOR_SPEED2_PID_KP, MOTOR_SPEED2_PID_KI, MOTOR_SPEED2_PID_KD};

int16_t GetEncoderSpeed(uint16_t ccr)
{
	if (ccr > 10000)
	{
		speed = 20000 - ccr;
	}
	else
	{
		speed = ccr;
	}
	return speed;
}
void Tracking_Init(void)
{
	PID_init(&motor[0], PID_POSITION, motor_speed1_pid, 3000, 100);
	PID_init(&motor[1], PID_POSITION, motor_speed2_pid, 3000, 100);
}
void Tracking(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	  

	while (1)
	{

		speed1 = GetEncoderSpeed(TIM3->CNT);
		angle1 += speed1;
		TIM3->CNT = 0;
		angle2 += speed2;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		TIM1->CNT = 0;
		feedback_1 = speed1; // 右轮
		feedback_2 = speed2;

		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if ((HAL_GPIO_ReadPin(huidu11_GPIO_Port, huidu11_Pin)) == 1 && (angle1 > 5500 || angle2 > 5500))
		{
			car_go_stop();

			break;
		}

		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 || (HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1)
		{
			// 直走
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(huidu12_GPIO_Port, huidu12_Pin)) == 1)
		{
			// 右转
			you_set_speed_1 = 15;
			zuo_set_speed_2 = 50;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(huidu16_GPIO_Port, huidu16_Pin)) == 1)
		{
			// 左转
			you_set_speed_1 = 50;
			zuo_set_speed_2 = 15;
			car_go_straight();
		}
		else
		{
			//
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
	}
}
void Trackinghou(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	  
	angle1 = 0;
	angle2 = 0;
	while (1)
	{

		flag[0] = (HAL_GPIO_ReadPin(HUIDU26_GPIO_Port, HUIDU26_Pin));
		flag[1] = (HAL_GPIO_ReadPin(HUIDU23_GPIO_Port, HUIDU23_Pin));

		speed1 = GetEncoderSpeed(TIM3->CNT);
		angle1 += speed1;
		TIM3->CNT = 0;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		angle2 += speed2;
		TIM1->CNT = 0;

		feedback_1 = speed1;
		feedback_2 = speed2;
		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if (((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 1) && ((angle1 >= 1000) || (angle2 > 1000)))
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}

		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 0)
		{
			// 后
			you_set_speed_1 = 30;
			zuo_set_speed_2 = 40;
			car_go_after();
		}
		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(HUIDU23_GPIO_Port, HUIDU23_Pin)) == 1)
		{
			flag[2] = 6;
			// 左转
			you_set_speed_1 = 10;
			zuo_set_speed_2 = 40;
			car_go_after();
		}
		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(HUIDU26_GPIO_Port, HUIDU26_Pin)) == 1)
		{
			// 右转
			flag[3] = 7;
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 10;
			car_go_after();
		}
		else
		{
			// 后
			you_set_speed_1 = 30;
			zuo_set_speed_2 = 40;
			car_go_after();
		}
	}
}

void Trackinghou2(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	  
	angle1 = 0;
	angle2 = 0;
	while (1)
	{
		speed1 = GetEncoderSpeed(TIM3->CNT);
		angle1 += speed1;
		TIM3->CNT = 0;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		angle2 += speed2;
		TIM1->CNT = 0;
		feedback_1 = speed1;
		feedback_2 = speed2;
		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if (((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 0) && ((angle1 >= 4000) || (angle2 >= 4000)))
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}

		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 0)
		{
			// 后
			you_set_speed_1 = 27;
			zuo_set_speed_2 = 37;
			car_go_after();
		}
		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(HUIDU23_GPIO_Port, HUIDU23_Pin)) == 1)
		{
			// 左转
			you_set_speed_1 = 10;
			zuo_set_speed_2 = 40;
			car_go_after();
			flag_ = 1;
		}
		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(HUIDU26_GPIO_Port, HUIDU26_Pin)) == 1)
		{
			// 右转

			you_set_speed_1 = 40;
			zuo_set_speed_2 = 10;
			car_go_after();
			flag_ = 2;
		}
		else
		{
			// 后
			you_set_speed_1 = 27;
			zuo_set_speed_2 = 37;
			car_go_after();
		}
	}
}

void Trackinghou3(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	  
	angle1 = 0;
	angle2 = 0;
	while (1)
	{
		speed1 = GetEncoderSpeed(TIM3->CNT);
		angle1 += speed1;
		TIM3->CNT = 0;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		angle2 += speed2;
		TIM1->CNT = 0;
		feedback_1 = speed1;
		feedback_2 = speed2;
		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if (((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 1) && ((angle1 >= 2000) || (angle2 >= 2000)))
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}

		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 0)
		{
			// 后
			you_set_speed_1 = 27;
			zuo_set_speed_2 = 37;
			car_go_after();
		}
		// else if ( (HAL_GPIO_ReadPin(huidu22_GPIO_Port,huidu22_Pin)) == 0 &&(HAL_GPIO_ReadPin(huidu24_GPIO_Port,huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port,huidu25_Pin)) == 0  )
		//{
		//	//后
		//	you_set_speed_1 = 50;
		//	zuo_set_speed_2 = 50;
		//	car_go_after();
		// }
		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(HUIDU23_GPIO_Port, HUIDU23_Pin)) == 1)
		{
			// 左转
			you_set_speed_1 = 10;
			zuo_set_speed_2 = 40;
			car_go_after();
			flag_ = 1;
		}
		else if ((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(HUIDU26_GPIO_Port, HUIDU26_Pin)) == 1)
		{
			// 右转

			you_set_speed_1 = 40;
			zuo_set_speed_2 = 10;
			car_go_after();
			flag_ = 2;
		}
		else
		{
			// 后
			you_set_speed_1 = 27;
			zuo_set_speed_2 = 37;
			car_go_after();
		}
	}
}
void zuozhuan1(void)
{

	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 22;
	zuo_set_speed_2 = 27;
	  
	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 435. || angle2 >= 435) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);
			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_left();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_left();
		}
	}
}
void zuozhuan2(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 22;
	zuo_set_speed_2 = 27;
	  

	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 800 || angle2 >= 800) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);

			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_left();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_left();
		}
	}
}
void zuozhuan3(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 22;
	zuo_set_speed_2 = 27;
	  

	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 1720 || angle2 >= 1720) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);

			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_left();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_left();
		}
	}
}
void youzhuan1(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 22;
	zuo_set_speed_2 = 27;
	  

	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 465 || angle2 >= 465) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);
			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_right();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_right();
		}
	}
}
void youzhuan2(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 20;
	zuo_set_speed_2 = 27;
	  
	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 900 || angle2 >= 900) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);

			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_right();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_right();
		}
	}
}

void youzhuan3(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 20;
	zuo_set_speed_2 = 27;
	  
	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 1550 || angle2 >= 1550) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);

			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_right();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_right();
		}
	}
}

void Tracking2(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	you_set_speed_1 = 24;
	zuo_set_speed_2 = 35;
	  
	angle1 = 0;
	angle2 = 0;
	int a = 0;
	while (1)
	{
		a++;
		if (a > 22)
		{
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);
			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			car_go_after();
		}
	}
}

void Tracking7(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	you_set_speed_1 = 24;
	zuo_set_speed_2 = 35;
	  
	angle1 = 0;
	angle2 = 0;
	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;

		if (angle1 >= 180 || angle2 >= 180)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);
			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			car_go_after();
		}
	}
}

void tuituitui(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	  
	while (1)
	{
		speed1 = GetEncoderSpeed(TIM3->CNT);
		TIM3->CNT = 0;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		TIM1->CNT = 0;
		feedback_1 = speed1; // 右轮
		feedback_2 = speed2;

		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if ((HAL_GPIO_ReadPin(huidu11_GPIO_Port, huidu11_Pin)) == 1)
		{
			car_go_stop();
			break;
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 || (HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1)
		{
			// 直走
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(huidu12_GPIO_Port, huidu12_Pin)) == 1)
		{
			// 右转
			you_set_speed_1 = 20;
			zuo_set_speed_2 = 50;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(huidu16_GPIO_Port, huidu16_Pin)) == 1)
		{
			// 左转
			you_set_speed_1 = 50;
			zuo_set_speed_2 = 20;
			car_go_straight();
		}
		else
		{
			// 直走
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
	}
}
void Tracking3(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	  

	while (1)
	{
		speed1 = GetEncoderSpeed(TIM3->CNT);
		angle1 += speed1;
		TIM3->CNT = 0;
		angle2 += speed2;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		TIM1->CNT = 0;
		feedback_1 = speed1; // 右轮
		feedback_2 = speed2;

		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if (((HAL_GPIO_ReadPin(huidu11_GPIO_Port, huidu11_Pin)) == 1) && (angle1 > 1200 || angle2 > 1200))
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}

		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 || (HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1)
		{
			// 直走
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(huidu12_GPIO_Port, huidu12_Pin)) == 1)
		{
			// 右转
			you_set_speed_1 = 20;
			zuo_set_speed_2 = 50;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(huidu16_GPIO_Port, huidu16_Pin)) == 1)
		{
			// 左转
			you_set_speed_1 = 50;
			zuo_set_speed_2 = 20;
			car_go_straight();
		}
		else
		{
			//
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
	}
}

void Tracking4(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	you_set_speed_1 = 40;
	zuo_set_speed_2 = 40;
	  
	int a = 0;
	while (1)
	{
		a++;
		if (a > 10)
		{
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);
			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			car_go_straight();
		}
	}
}
void Tracking5(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	  

	while (1)
	{
		speed1 = GetEncoderSpeed(TIM3->CNT);
		angle1 += speed1;
		TIM3->CNT = 0;
		angle2 += speed2;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		TIM1->CNT = 0;
		feedback_1 = speed1; // 右轮
		feedback_2 = speed2;

		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if (((HAL_GPIO_ReadPin(huidu11_GPIO_Port, huidu11_Pin)) == 1) && (angle1 > 700 || angle2 > 700))
		{
			car_go_stop();
			break;
		}

		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 || (HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1)
		{
			// 直走
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(huidu12_GPIO_Port, huidu12_Pin)) == 1)
		{
			// 右转
			you_set_speed_1 = 20;
			zuo_set_speed_2 = 50;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(huidu16_GPIO_Port, huidu16_Pin)) == 1)
		{
			// 左转
			you_set_speed_1 = 50;
			zuo_set_speed_2 = 20;
			car_go_straight();
		}
		else
		{
			//
			you_set_speed_1 = 40;
			zuo_set_speed_2 = 42;
			car_go_straight();
		}
	}
}
void Tracking6(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	  

	while (1)
	{
		speed1 = GetEncoderSpeed(TIM3->CNT);
		angle1 += speed1;
		TIM3->CNT = 0;
		angle2 += speed2;
		speed2 = GetEncoderSpeed(TIM1->CNT);
		TIM1->CNT = 0;
		feedback_1 = speed1; // 右轮
		feedback_2 = speed2;

		PID_calc(&motor[0], feedback_1, you_set_speed_1);
		PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
		TIM9->CCR1 = motor[0].out;
		TIM9->CCR2 = motor[1].out;
		HAL_Delay(50);
		if ((((HAL_GPIO_ReadPin(huidu22_GPIO_Port, huidu22_Pin)) == 1) && (HAL_GPIO_ReadPin(huidu25_GPIO_Port, huidu25_Pin) == 1) && (HAL_GPIO_ReadPin(huidu24_GPIO_Port, huidu24_Pin) == 1)) && (angle1 > 2950 || angle2 > 2950))
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}

		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 || (HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1)
		{
			// 直走
			you_set_speed_1 = 51;
			zuo_set_speed_2 = 52;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 1 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 0 ||
				 (HAL_GPIO_ReadPin(huidu12_GPIO_Port, huidu12_Pin)) == 1)
		{
			// 右转
			you_set_speed_1 = 20;
			zuo_set_speed_2 = 50;
			car_go_straight();
		}
		else if ((HAL_GPIO_ReadPin(huidu13_GPIO_Port, huidu13_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 0 && (HAL_GPIO_ReadPin(huidu15_GPIO_Port, huidu15_Pin)) == 1 ||
				 (HAL_GPIO_ReadPin(huidu16_GPIO_Port, huidu16_Pin)) == 1)
		{
			// 左转
			you_set_speed_1 = 50;
			zuo_set_speed_2 = 20;
			car_go_straight();
		}
		else
		{
			//
			you_set_speed_1 = 51;
			zuo_set_speed_2 = 52;
			car_go_straight();
		}
	}
}

void zuozhuan1_3(void)
{

	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 22;
	zuo_set_speed_2 = 27;
	  
	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 400. || angle2 >= 400) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);
			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_left();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_left();
		}
	}
}
void zuozhuan2_3(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 22;
	zuo_set_speed_2 = 27;
	  

	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 700 || angle2 >= 700) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);

			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_left();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_left();
		}
	}
}

void youzhuan1_3(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 22;
	zuo_set_speed_2 = 27;
	  

	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 450 || angle2 >= 450) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);
			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_right();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_right();
		}
	}
}
void youzhuan2_3(void)
{
	PID_clear(&motor[0]);
	PID_clear(&motor[1]);
	angle1 = 0;
	angle2 = 0;
	you_set_speed_1 = 20;
	zuo_set_speed_2 = 27;
	  
	while (1)
	{
		angle1 += speed1;
		angle2 += speed2;
		if ((angle1 >= 930 || angle2 >= 930) && (HAL_GPIO_ReadPin(huidu14_GPIO_Port, huidu14_Pin)) == 1)
		{
			angle1 = 0;
			angle2 = 0;
			car_go_stop();
			break;
		}
		else
		{
			speed1 = GetEncoderSpeed(TIM3->CNT);

			TIM3->CNT = 0;
			speed2 = GetEncoderSpeed(TIM1->CNT);
			TIM1->CNT = 0;
			feedback_1 = speed1; // 右轮
			feedback_2 = speed2;
			turn_right();
			PID_calc(&motor[0], feedback_1, you_set_speed_1);
			PID_calc(&motor[1], feedback_2, zuo_set_speed_2);
			TIM9->CCR1 = motor[0].out;
			TIM9->CCR2 = motor[1].out;
			HAL_Delay(50);
			turn_right();
		}
	}
}
