#include "encoder.h"

  

Motor motor1;

  

void Motor_Init(void)

{

    HAL_TIM_Encoder_Start(&ENCODER_TIM, TIM_CHANNEL_ALL);      //开启编码器定时器

    __HAL_TIM_ENABLE_IT(&ENCODER_TIM,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理

    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //开启10ms定时器中断

    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //开启PWM

    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //开启PWM

    __HAL_TIM_SET_COUNTER(&ENCODER_TIM, 10000);                //编码器定时器初始值设定为10000

    motor1.lastCount = 0;                                   //结构体内容初始化

    motor1.totalCount = 0;

    motor1.overflowNum = 0;                                  

    motor1.speed = 0;

    motor1.direct = 0;

}

  

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//定时器回调函数，用于计算速度

{

    if(htim->Instance==ENCODER_TIM.Instance)//编码器输入定时器溢出中断                    

    {      

        if(COUNTERNUM < 10000) motor1.overflowNum++;       //如果是向上溢出

        else if(COUNTERNUM >= 10000) motor1.overflowNum--; //如果是向下溢出

        __HAL_TIM_SetCounter(&ENCODER_TIM, 10000);             //重新设定初始值

    }

    else if(htim->Instance==GAP_TIM.Instance)//间隔定时器中断，是时候计算速度了

    {

        motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//如果向上计数（正转），返回值为0，否则返回值为1

        motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值

        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10;//算得每秒多少转

        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//算得车轮线速度每秒多少毫米

        motor1.lastCount = motor1.totalCount; //记录这一次的计数值

    }

}
