#include "bsp.h"


/**************************************************************************
 * 
 *Function Name:void power_on_key_short_fun(void)
 *Function:
 *Input Ref:
 *Return Ref:
 * 
*****************************************************************************/
void power_on_key_short_fun(void)
{
  
   
   if(gpro_t.smart_phone_app_timer_power_on_flag == 0){

    	run_t.gModel =1; //WT.EDIT 2022.09.01
    	run_t.gPlasma=1;
    	run_t.gDry =1;
    	run_t.gUltransonic =1;
    
    }

	gpro_t.set_temp_value_success =0;
    run_t.smart_phone_set_temp_value_flag=0;
    run_t.timer_time_hours =40;
    
    
    run_t.disp_wind_speed_grade =100;

    
	

   run_t.display_set_timer_or_works_mode =works_time;

	
     run_t.gTimer_timing=0;

	 run_t.timer_time_hours =0;
	 run_t.timer_time_minutes =0;
	 

	 run_t.timer_timing_define_flag = timing_not_definition;

	 

	 if(lcd_t.display_beijing_time_flag == 0 ){

	 run_t.gTimer_disp_time_seconds=0;
	 run_t.dispTime_hours=0;
     run_t.dispTime_minutes=0;
	 
	  lcd_t.number5_low=(run_t.dispTime_hours ) /10;
     lcd_t.number5_high =(run_t.dispTime_hours) /10;

	 lcd_t.number6_low = (run_t.dispTime_hours ) %10;;
	 lcd_t.number6_high = (run_t.dispTime_hours ) %10;
     
     lcd_t.number7_low = (run_t.dispTime_minutes )/10;
	 lcd_t.number7_high = (run_t.dispTime_minutes )/10;

	 lcd_t.number8_low = (run_t.dispTime_minutes )%10;
	 lcd_t.number8_high = (run_t.dispTime_minutes )%10;
	
	 
	 }
    
	run_t.power_off_id_flag =1;
 
   

    run_t.gModel =1; //AI mode
    run_t.display_set_timer_or_works_mode=works_time ;
  
  
     Lcd_PowerOn_Fun();
     freertos_stop_timer1_handler();
    
}


/**************************************************************************
 * 
 *Function Name:void power_key_long_fun(void)
 *Function:
 *Input Ref:
 *Return Ref:
 * 
*****************************************************************************/
void power_key_long_fun(void)
{
    
    run_t.wifi_link_net_success =0;
    run_t.gTimer_wifi_connect_counter=0;
  
    run_t.wifi_receive_led_fast_led_flag=0; //adjust if mainboard receive of connect wifi of signal
    run_t.wifi_led_fast_blink_flag=1;
  
}

/**************************************************************************
 * 
 *Function Name:void power_on_off_handler(void)
 *Function:
 *Input Ref:
 *Return Ref:
 * 
*****************************************************************************/
void power_on_off_handler(void)
{
    if(run_t.gPower_On == power_off){
       // run_t.gPower_On = power_on;
        gpro_t.long_key_power_counter =0; 
        run_t.power_on_disp_smg_number = 1;
        gpro_t.send_ack_cmd = ack_power_on;
        gpro_t.gTimer_again_send_power_on_off =0;
        SendData_PowerOnOff(1);
         gpro_t.power_on_every_times=1;

        gpro_t.gTimer_mode_key_long=0;
        osDelay(3);//HAL_Delay(10);
      

    }
    else{
        gpro_t.long_key_power_counter=0; //WT.2024.11.05
        gpro_t.key_long_power_flag=0;
        gpro_t.send_ack_cmd = ack_power_off;
        gpro_t.gTimer_again_send_power_on_off =0;
        SendData_PowerOnOff(0);
        osDelay(3);//HAL_Delay(10);
        //run_t.gPower_On = power_off;


    }
    
}



