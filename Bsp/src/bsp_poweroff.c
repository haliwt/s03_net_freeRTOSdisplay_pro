#include "bsp.h"


void power_off_handler(void)
{
    
    if(run_t.power_off_id_flag == 1){   
        run_t.power_off_id_flag++;  
        lcd_donot_disp_screen();
        Power_Off_Fun();
    

        LED_MODEL_OFF();
        POWER_ON_LED();

        run_t.wifi_led_fast_blink_flag=0;
        run_t.smart_phone_set_temp_value_flag=0;
        run_t.timer_time_hours =0;
        run_t.timer_time_minutes =0;

        run_t.fan_warning=0;
        run_t.ptc_warning = 0;

        //run_t.gModel =1; //WT.EDIT 2022.09.01
        run_t.gPlasma=0;
        run_t.gDry =0;
        run_t.gUltransonic =0;


        run_t.timer_timing_define_flag = timing_not_definition;

        run_t.disp_wind_speed_grade =100;	

        run_t.fan_off_60s =0;
        run_t.gFan_RunContinue=1;
        gpro_t.smart_phone_app_timer_power_on_flag =0;
      
	}
    
	lcd_power_off_donot_fan_Fun();
   
    Breath_Led();
	if(run_t.gFan_RunContinue == 1){
       if(run_t.fan_off_60s < 61){
       
	      LCD_BACK_LIGHT_ON();
	      LCD_Display_Wind_Icon_Handler();
       	}
	   else {
         
           run_t.gFan_RunContinue =0;
		   Lcd_PowerOff_Fun();

	   }
	}
}


/************************************************************************
	*
	*Function Name: static void Power_Off_Fun(void)
	*
	*
	*
	*
************************************************************************/
 void Power_Off_Fun(void)
{
	
        //run_t.gModel =1; //WT.EDIT 2022.09.01
		run_t.gPlasma=0;
		run_t.gDry =0;
		run_t.gUltransonic =0;

		run_t.gPower_On=power_off;
		
		run_t.wifi_led_fast_blink_flag=0;
		run_t.timer_timing_define_flag = timing_not_definition;
		
		run_t.disp_wind_speed_grade =30;	
		
		run_t.fan_off_60s =0;
} 



