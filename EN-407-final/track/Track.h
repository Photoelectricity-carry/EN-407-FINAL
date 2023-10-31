#ifndef __TRACK_H_
#define __TRACK_H_

#include "main.h"

//ËÙ¶È»·pid
#define MOTOR_SPEED2_PID_KP 123.0f
#define MOTOR_SPEED2_PID_KI 	0.0f
#define MOTOR_SPEED2_PID_KD 	14.0f

#define MOTOR_SPEED1_PID_KP  120.0f
#define MOTOR_SPEED1_PID_KI  0.0f
#define MOTOR_SPEED1_PID_KD  6.0f

typedef struct {
	uint16_t id;
	GPIO_TypeDef *huidu11;
	uint16_t GPIO_Pin;
}huidu_t;

uint8_t huidu_check(huidu_t* sensor);

void Tracking_Init(void);

extern void Tracking(void);
extern void Tracking1(void);
extern void Tracking2(void);
extern void Tracking3(void);
extern void Tracking4(void);
extern void Tracking5(void);
extern void Tracking6(void);
extern void Tracking7(void);
extern void Trackinghou_transmit(void);
extern void Trackinghou(void);
extern void Trackinghou2(void);
extern void Trackinghou3(void);
extern void zuozhuan1(void);
extern void zuozhuan2(void);
extern void zuozhuan3(void);
extern void youzhuan1(void);
extern void youzhuan2(void);
extern void youzhuan3(void);
extern void tuituitui(void);
extern void zuozhuan1_3(void);
extern void zuozhuan2_3(void);
extern void youzhuan1_3(void);
extern void youzhuan2_3(void);



#endif
