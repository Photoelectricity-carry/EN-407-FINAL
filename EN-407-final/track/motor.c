#include "motor.h"

extern int16_t you_set_speed_1;
extern int16_t zuo_set_speed_2;
// ǰ��
void car_go_straight(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_SET);
}

// Ѳ����ת
void car_go_right(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_SET);
}

// Ѳ����ת
void car_go_left(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}

// ԭ����ת
void turn_right(void)
{
   //	you_set_speed_1 = 60;
   //	zuo_set_speed_2 = 60;
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}

// ԭ����ת
void turn_left(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_SET);
}
// ֹͣ
void car_go_stop(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}

// ����
void car_go_after(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port, motor11_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port, motor12_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port, motor21_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port, motor22_Pin, GPIO_PIN_RESET);
}
