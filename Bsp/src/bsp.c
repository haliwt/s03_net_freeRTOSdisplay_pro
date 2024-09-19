#include "bsp.h"

process_state gpro_t;


static void  disp_set_timer_timing_value_fun(void);

static void disp_normal_timing_handler(void);

static void fan_default_warning_fun(void);

static void ptc_high_temp_warning_fun(void);


void bsp_init(void)
{
  Beijing_Time_Init();
  bsp_wifi_init();

}


void mode_key_long_fun(void)
{
   
   if(run_t.ptc_warning ==0){

       run_t.gModel=2;
     //  run_t.setup_timer_timing_item=1;//run_t.gModel =2;
       run_t.display_set_timer_or_works_mode = setup_timer;
      
       run_t.gTimer_key_timing=0;


   
   }

}

void display_timer_and_beijing_time_handler(void)
{
   
  // DISP_STATE  disp_state;
   switch(run_t.display_set_timer_or_works_mode){//switch(run_t.setup_timer_timing_item){

    case works_time:
      disp_normal_timing_handler(); 
    //  beijing_time_fun();
    
     Setup_Timer_Times_Donot_Display();

    break;

    

    case setup_timer:

      disp_set_timer_timing_value_fun();

    break;

    case timer_time:
        
        disp_timer_run_times();
		Works_Counter_Time();

    break;

    case FAN_WARNING: //fan warning 

      
         fan_default_warning_fun();
         if(run_t.ptc_warning == 1){

             if(gpro_t.gTimer_fan_to_ptc_warning > 2){

                   gpro_t.gTimer_fan_to_ptc_warning = 0;
               
               //run_t.setup_timer_timing_item = PTC_WARNING ;

                 run_t.display_set_timer_or_works_mode = PTC_WARNING;

            }

         }

    break;

    case PTC_WARNING: //ptc warning

         ptc_high_temp_warning_fun();
         if(run_t.fan_warning == 1){

             if(gpro_t.gTimer_fan_to_ptc_warning > 2){

                   gpro_t.gTimer_fan_to_ptc_warning = 0;
               
               //run_t.setup_timer_timing_item = FAN_WARNING ;
               run_t.display_set_timer_or_works_mode =FAN_WARNING;

            }

         }

    break;

    }

}

/******************************************************************************
	*
	*Function Name:void disp_normal_timing_handler(void)
	*Function: display of icon , "1" -> ON ,"0"-> OFF
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************************/
static void disp_normal_timing_handler(void)
{

      if(run_t.gTimer_disp_timer_seconds >59){ //minute
		
		run_t.gTimer_disp_timer_seconds=0;
        run_t.dispTime_minutes ++;
       
          
		if(run_t.dispTime_minutes > 59){
			run_t.dispTime_minutes=0;
			run_t.dispTime_hours ++;
		    
		if(run_t.dispTime_hours >24){
			run_t.dispTime_hours=0;

		}

		}


	  } 
    

}



/**************************************************************************************************
*
*Function Name:void static disp_set_timer_timing_value_fun(void)
*
*
*
*****************************************************************************************************/
static void disp_set_timer_timing_value_fun(void)
{
  
     static uint8_t tim_bit_1_hours,tim_bit_2_hours;

      if(run_t.gTimer_key_timing < 4){

            tim_bit_2_hours = run_t.timer_time_hours /10 ;
			tim_bit_1_hours = run_t.timer_time_hours %10;
           // HAL_Delay(20);
			run_t.timer_time_minutes  =0;

			
            
			lcd_t.number5_low=tim_bit_2_hours;
			lcd_t.number5_high =tim_bit_2_hours;

			lcd_t.number6_low = tim_bit_1_hours;
			lcd_t.number6_high = tim_bit_1_hours;

			lcd_t.number7_low=0;
			lcd_t.number7_high =0;

			lcd_t.number8_low = 0;
			lcd_t.number8_high = 0;

       
    
      if(run_t.gTimer_digital5678_ms < 3){
                 TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber4_Low[lcd_t.number4_low]+lcdNumber5_High[lcd_t.number5_high]) & 0xff);//display digital '4,5'
                 TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[lcd_t.number5_low]+lcdNumber6_High[lcd_t.number6_high]) & 0xff);
                 TM1723_Write_Display_Data(0xCB,(0x01+lcdNumber6_Low[lcd_t.number6_low]+lcdNumber7_High[lcd_t.number7_high]) & 0xff);
                 TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[lcd_t.number7_low]+lcdNumber8_High[lcd_t.number8_high]) & 0xff);
                 if(run_t.disp_wind_speed_grade >66){
                    TM1723_Write_Display_Data(0xCE,(T13+lcdNumber8_Low[lcd_t.number8_low]+ WIND_SPEED_FULL) & 0xff);
                  }
                  else if(run_t.disp_wind_speed_grade >33 && run_t.disp_wind_speed_grade <67){
                     TM1723_Write_Display_Data(0xCE,(T13+lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_TWO) & 0xff);
    
                  }
                  else if(run_t.disp_wind_speed_grade <34){
                     TM1723_Write_Display_Data(0xCE,(T13+lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_ONE) & 0xff);
                  }

                  TM1723_Write_Display_Data(0xCF,(T16+T11)&0x05);//
       }
       else if(run_t.gTimer_digital5678_ms > 2 && run_t.gTimer_digital5678_ms < 5){
                 TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber4_Low[lcd_t.number4_low]+lcdNumber5_High[lcd_t.number5_high]) & 0x0f);//display digital '4,5'
                 TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[lcd_t.number5_low]+lcdNumber6_High[lcd_t.number6_high]) & 0x01);
                 TM1723_Write_Display_Data(0xCB,(0x01+lcdNumber6_Low[lcd_t.number6_low]+lcdNumber7_High[lcd_t.number7_high]) & 0x01);
                 TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[lcd_t.number7_low]+lcdNumber8_High[lcd_t.number8_high]) & 0x01);
                 if(run_t.disp_wind_speed_grade >66){
                    TM1723_Write_Display_Data(0xCE,(lcdNumber8_Low[lcd_t.number8_low]+ WIND_SPEED_FULL) & 0xE1);
                 }
                 else if(run_t.disp_wind_speed_grade >33 && run_t.disp_wind_speed_grade <67){
                     TM1723_Write_Display_Data(0xCE,(lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_TWO) & 0xE1);
                 }
                  else if(run_t.disp_wind_speed_grade <34){
                     TM1723_Write_Display_Data(0xCE,(lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_ONE) & 0xE1);
                 }

                 TM1723_Write_Display_Data(0xCF,((T16+T12+T10)&0x0B));//
       }
             
       if(run_t.gTimer_digital5678_ms > 3){ //4
           run_t.gTimer_digital5678_ms=0;
               

        }

       }
       else{ //4
              //run_t.setup_timer_timing_item=0;//run_t.gModel =2;
            //  run_t.display_set_timer_or_works_mode = WORKS_TIME;
              run_t.timer_time_minutes = 0;
              run_t.gTimer_timing=0;
               if(run_t.timer_time_hours !=0){  
                      run_t.timer_timing_define_flag = timing_success;
                      run_t.display_set_timer_or_works_mode = timer_time;
                }
                else{
                     run_t.timer_timing_define_flag = timing_not_definition ;

                     run_t.display_set_timer_or_works_mode = works_time;

                }
         
    
      }
                
                
    TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);

 }
/**************************************************************************************************
*
*Function Name:void set_temperature_compare_value_fun(void)
*
*
*
*****************************************************************************************************/
void set_temperature_compare_value_fun(void)
{

    static uint8_t first_on_ptc;

    if(gpro_t.temp_key_set_value ==1 && gpro_t.gTimer_set_temp_times > 1){
    
         run_t.setup_temperature_value =1;
          gpro_t.temp_key_set_value =0;
          gpro_t.gTimer_temp_compare_value =0;

    }
    else if(gpro_t.set_temp_value_success == 1 && gpro_t.gTimer_temp_compare_value > 3 && gpro_t.temp_key_set_value ==0){

       gpro_t.gTimer_temp_compare_value =0;

      if(run_t.wifi_set_temperature > gpro_t.temp_real_value && gpro_t.smart_phone_turn_off_ptc_flag ==0){

            run_t.gDry = 1;
            SendData_Set_Command(0x22,0x01); //open ptc 
            osDelay(10);
            SendData_Temp_Data(run_t.wifi_set_temperature);
            
      }
      else{
           run_t.gDry = 0;
           SendData_Set_Command(0x22,0x00); //close ptc 
           osDelay(10);

           SendData_Temp_Data(run_t.wifi_set_temperature);


      }



    }
    else if(gpro_t.set_temp_value_success == 0 && gpro_t.gTimer_temp_compare_value > 5 && gpro_t.temp_key_set_value ==0){ 
        
        if(gpro_t.temp_real_value > 39){ // must be clouse ptc.
    
               first_on_ptc = 1;
               run_t.gDry = 0;
               SendData_Set_Command(0x22,0x00); //close ptc 
          }
          else if(first_on_ptc == 1){
               
                 
               if(gpro_t.temp_real_value < 38){
                       run_t.gDry = 1;
                       SendData_Set_Command(0x22,0x01); //open ptc  
                }
                   

          }
              
    }

}
/**************************************************************************************************
*
*Function Name:void set_temperature_compare_value_fun(void)
*Function : fan of warning ,fan of leaf stop
*
*
****************************************************************************************************/
static void fan_default_warning_fun(void)
{

   TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber4_Low[lcd_t.number4_low]+lcdNumber5_High_E[0]));//display digital 'E'
   TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'  
    if(lcd_t.gTimer_colon_ms < 6){           
         TM1723_Write_Display_Data(0xCB,0x01+lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//display "6,7"
    }
   else if(lcd_t.gTimer_colon_ms > 5 && lcd_t.gTimer_colon_ms < 11){
      TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//
   }
   else 
   {
      lcd_t.gTimer_colon_ms = 0;
   }
   TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[0]+lcdNumber8_High[2]);//display "02'
   TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[2]);//display "t,c"
   TM1723_Write_Display_Data(0xCF,(T10+T11+T12+T16));//

}
/**************************************************************************************************
*
*Function Name:static void ptc_high_temp_warning_fun(void)
*Function : fan of warning ,fan of leaf stop
*Input Ref:
*Return Ref:
*
****************************************************************************************************/
static void ptc_high_temp_warning_fun(void)
{
   
    TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber4_Low[lcd_t.number4_low]+lcdNumber5_High_E[0]));//display digital 'E'
   // TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'  
    if(lcd_t.gTimer_colon_ms < 6){           
        TM1723_Write_Display_Data(0xCB,0x01+lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//display "6,7"
    }
    else if(lcd_t.gTimer_colon_ms > 5 && lcd_t.gTimer_colon_ms < 11){
        TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//
    }
    else 
    {
        lcd_t.gTimer_colon_ms = 0;
    }
   // TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[0]+lcdNumber8_High[1]);//display "01'
   // TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[1]);//display "t,c"
   // TM1723_Write_Display_Data(0xCF,(T10+T11+T12+T16));//


    /***************************fan of leaf *********************************************/
    if(lcd_t.gTimer_fan_10ms >39 && lcd_t.gTimer_fan_10ms<80){

  

    
        TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display 
        TM1723_Write_Display_Data(0xCC,lcdNumber7_Low[0]+lcdNumber8_High[1]);//display "7,8'
        TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[1]);//display "t,c"
        TM1723_Write_Display_Data(0xCF,((T11+T16)& 0x05));//
               
   }
   else if(lcd_t.gTimer_fan_10ms <40){
                
   
    TM1723_Write_Display_Data(0xCA,lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital '5,6'
    TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[0]+lcdNumber8_High[1]);//display "t,c
    TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]);//display "1"
   
    TM1723_Write_Display_Data(0xCF,((T16+T12+T10)&0x0B));//
              
  }
  else if(lcd_t.gTimer_fan_10ms > 79){
             lcd_t.gTimer_fan_10ms=0;
  }

}





