#ifndef __BSP_FREERTOS_H
#define __BSP_FREERTOS_h
#include "main.h"





void freeRTOS_Handler(void);


void App_PowerOn_Handler(void);

void App_PowerOff_Handler(void);

void freertos_start_timer1_handler(void);

void freertos_stop_timer1_handler(void);

void freertos_start_timer2_handler(void);


#endif 



