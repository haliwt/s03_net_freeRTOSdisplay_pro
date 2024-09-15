#ifndef __BSP_KEY_APP_
#define __BSP_KEY_APP_
#include "main.h"

typedef enum{

    power_off,
	power_on


}run_prcess_state;


typedef enum{

    beijing_time,
	timer_time,
	ai_item,
	ai_not_item

}beijing_time_stat;



typedef enum{

   power_key = 0x01,
   link_cloud_key = 0x81, //long key
   model_key=0x02,   //short Key
   model_long_key= 0x82, //longk key
   add_key=0x08,
   dec_key=0x04,
   power_on_special_key=0xAA
}key_item_t;

typedef enum _time_t{

   time_timing= 0x01,
   time_normal,
   time_gmt

}time_state_t;

typedef enum _WIFI_POWER_STATE_{
	WIFI_POWER_ON_ITEM = 0x01,
	WIFI_POWER_OFF_ITEM,
	WIFI_POWER_NULL

}wifi_power_state;

typedef enum{

	 DRY_ON = 0x40,
	 DRY_OFF = 0x41,

	 DRY_ON_NO_BUZZER = 0x90,
	 DRY_OFF_NO_BUZZER = 0x91,

	 PLASMA_ON = 0x20,
	 PLASMA_OFF = 0x21,

	 FAN_ON =0x10,
	 FAN_OFF = 0x11,

	 MODE_AI = 0x04,
	 MODE_TIMER = 0x14,
	 MODE_AI_NO_BUZZER= 0x44,

	 WIFI_CONNECT_FAIL=0x55,

	 WIFI_CONNECT_SUCCESS= 0xAA
	 



}works_t;


extern void (*single_ai_fun)(uint8_t cmd);
extern void (*single_add_fun)(void);
extern void (*sendAi_usart_fun)(uint8_t senddat);
extern void (*beijing_time_fun)(void);

void Scan_KeyModel(void);



void Single_AI_RunCmd(void (*singlaieHandler)(uint8_t dat));

void Single_Add_RunCmd(void(*addHandler)(void));

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void));

void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat));



void Power_Off_Fun(void);

void power_off_handler(void);


void Process_Key_Handler(uint8_t keylabel);

void Beijing_Time_Display_Handler(void(*beijing_time_handler)(void));
void Beijing_Time_Init(void);



void power_on_key_short_fun(void);


void power_key_long_fun(void);


void mode_key_short_fun(void);





void add_key_fun(void);

void dec_key_fun(void);




#endif 

