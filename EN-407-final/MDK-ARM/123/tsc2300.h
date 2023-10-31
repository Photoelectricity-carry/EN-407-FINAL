#ifndef __TCS2300_H
#define __TCS2300_H
#include "main.h"

extern uint16_t amount;

extern uint16_t Rgena,Ggena,Bgena;
extern uint16_t Ramount,Gamount,Bamount;
extern void tsc2300(void);

//#define S0 PBout(11)
//#define S1 PBout(12)
//#define S2 PBout(14)
//#define S3 PBout(13)
//#define OUT PEin(4)

void tcs2300(int color_t);
void whitebalance(void);
void aj(void);
void tcs2300_turn(int color_t);

uint16_t tcs2300_RED(void);
uint16_t tcs2300_GREEN(void);
uint16_t tcs2300_BLUE(void);
uint16_t rgb(void);

#endif
