#include "motor.h"

extern int16_t you_set_speed_1;
extern int16_t zuo_set_speed_2;
// 前进
void car_go_straight(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_SET);
}

// 巡线右转
void car_go_right(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_SET);
}

// 巡线左转
void car_go_left(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}

// 原地左转
void turn_right(void)
{
   //	you_set_speed_1 = 60;
   //	zuo_set_speed_2 = 60;
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}

// 原地右转
void turn_left(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_SET);
}
// 停止
void car_go_stop(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}

// 后退
void car_go_after(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}
