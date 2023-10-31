#ifndef _ENCODER_H_

#define _ENCODER_H_

  

#include "stm32f4xx.h"

  

//���1�ı�������������

#define MOTO1_ENCODER1_PORT GPIOA

#define MOTO1_ENCODER1_PIN  GPIO_PIN_0

#define MOTO1_ENCODER2_PORT GPIOA

#define MOTO1_ENCODER2_PIN  GPIO_PIN_1

  

//��ʱ����

#define ENCODER_TIM htim2

#define PWM_TIM     htim3

#define GAP_TIM     htim4

  

#define MOTOR_SPEED_RERATIO 45u    //������ٱ�

#define PULSE_PRE_ROUND 11 //һȦ���ٸ�����

#define RADIUS_OF_TYRE 34 //��̥�뾶����λ����

#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14

  

#define RELOADVALUE __HAL_TIM_GetAutoreload(&ENCODER_TIM)    //��ȡ�Զ�װ��ֵ,������Ϊ20000

#define COUNTERNUM __HAL_TIM_GetCounter(&ENCODER_TIM)        //��ȡ��������ʱ���еļ���ֵ

  

typedef struct _Motor

{

    int32_t lastCount;   //��һ�μ���ֵ

    int32_t totalCount;  //�ܼ���ֵ

    int16_t overflowNum; //�������

    float speed;         //���ת��

    uint8_t direct;      //��ת����

}Motor;

  

#endif
