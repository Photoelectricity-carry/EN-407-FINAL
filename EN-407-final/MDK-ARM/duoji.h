#ifndef __duoji_H_
#define __duoji_H_

/*
TIM2CH1 Բ��
TIM2CH3 4��
TIM4CH1 1��
TIM4CH2 2��
TIM4CH3 3��
TIM4CH4 5��
*/

//void DISC_Rotate_Anticlockwise(int time);			//500
//void DISC_Rotate_Clockwise(int time);					//900
void DISC_Rotate(int pwm_t);
void MG90S_Rotate_down1(void);
void MG90S_Rotate_up1(void);

void MG90S_Rotate_down2(void);
void MG90S_Rotate_up2(void);
     
void MG90S_Rotate_down3(void);		//���Ŷ����
void MG90S_Rotate_up3(void);
     
void MG90S_Rotate_down4(void);    //�ĺ�
void MG90S_Rotate_up4(void);
     
void MG90S_Rotate_down5(void);
void MG90S_Rotate_up5(void);


#endif
