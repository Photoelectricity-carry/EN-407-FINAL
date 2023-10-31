#include "encoder.h"

  

Motor motor1;

  

void Motor_Init(void)

{

    HAL_TIM_Encoder_Start(&ENCODER_TIM, TIM_CHANNEL_ALL);      //������������ʱ��

    __HAL_TIM_ENABLE_IT(&ENCODER_TIM,TIM_IT_UPDATE);           //������������ʱ�������ж�,���������

    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //����10ms��ʱ���ж�

    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //����PWM

    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //����PWM

    __HAL_TIM_SET_COUNTER(&ENCODER_TIM, 10000);                //��������ʱ����ʼֵ�趨Ϊ10000

    motor1.lastCount = 0;                                   //�ṹ�����ݳ�ʼ��

    motor1.totalCount = 0;

    motor1.overflowNum = 0;                                  

    motor1.speed = 0;

    motor1.direct = 0;

}

  

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//��ʱ���ص����������ڼ����ٶ�

{

    if(htim->Instance==ENCODER_TIM.Instance)//���������붨ʱ������ж�                    

    {      

        if(COUNTERNUM < 10000) motor1.overflowNum++;       //������������

        else if(COUNTERNUM >= 10000) motor1.overflowNum--; //������������

        __HAL_TIM_SetCounter(&ENCODER_TIM, 10000);             //�����趨��ʼֵ

    }

    else if(htim->Instance==GAP_TIM.Instance)//�����ʱ���жϣ���ʱ������ٶ���

    {

        motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1

        motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ

        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10;//���ÿ�����ת

        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//��ó������ٶ�ÿ����ٺ���

        motor1.lastCount = motor1.totalCount; //��¼��һ�εļ���ֵ

    }

}
