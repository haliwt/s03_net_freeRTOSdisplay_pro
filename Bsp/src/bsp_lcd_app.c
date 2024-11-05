#include "bsp.h"


static void Display_Kill_Dry_Ster_Icon(void);
static void disp_fan_speed_level(void);

static void donot_disp_T13_icon_fan_speed_level(void);

static void disp_fan_ptc_warning_time_colon_fun(void);

static void works_timer_disp_numaber(void);

//


/*************************************************************************
 	*
 	* Function Name:void disp_temp_humidity_value(void)
 	* Function :lcd display panel 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void disp_temp_humidity_wifi_icon_handler(void)
{
    
     static uint8_t decade_temp,unit_temp,temp1,temp2;

     static uint8_t number_blink_times, disp_set_timer_value;
	
	 TIM1723_Write_Cmd(0x00);
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

   /***********************setup temperature value ********************************/
	 //digital 1,2 ->display "temperature"  blink  
	if(run_t.smart_phone_set_temp_value_flag ==1){

        disp_set_timer_value =1;

        decade_temp = run_t.wifi_set_temperature / 10 ;
		unit_temp =  run_t.wifi_set_temperature % 10; //
        
		lcd_t.number1_low=decade_temp;
		lcd_t.number1_high =decade_temp;

		lcd_t.number2_low = unit_temp;
		lcd_t.number2_high = unit_temp;

	     
	 if(run_t.gTimer_numbers_one_two_blink < 6  ){ //disp number
	     //display address 0xC2
	     if(run_t.gDry ==1 && run_t.gPlasma ==1  && run_t.gUltransonic==1)
		 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
         else if(run_t.gDry ==0 && run_t.gPlasma ==1 && run_t.gUltransonic==1)
		 	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
         else if(run_t.gDry ==0 && run_t.gPlasma ==0 && run_t.gUltransonic==1)
		 	TM1723_Write_Display_Data(0xC2,(0X01+BUG_Symbol+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
		 else if(run_t.gDry ==0 && run_t.gPlasma ==0 && run_t.gUltransonic==0){
		 	TM1723_Write_Display_Data(0xC2,(0X01+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
		 }
		 else if(run_t.gDry ==1 && run_t.gPlasma ==1 && run_t.gUltransonic==0){
		 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
		 }
		 else if(run_t.gDry ==0 && run_t.gPlasma ==1 && run_t.gUltransonic==0){
		 	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
		 }
		 else if(run_t.gDry ==1 && run_t.gPlasma ==0 && run_t.gUltransonic==0){
		 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
		 }
		 else if(run_t.gDry ==1 && run_t.gPlasma ==0 && run_t.gUltransonic==1){
		 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0xff);//display digital "temp
		 }
		 //display addres 0xC3 -> AI icon
		 if(run_t.gModel ==1)
	        TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[lcd_t.number1_low]+AI_Symbol+lcdNumber2_High[lcd_t.number2_high]) & 0xff);//display  "AI icon
         else
		 	TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[lcd_t.number1_low]+AI_NO_Symbol+lcdNumber2_High[lcd_t.number2_high]) & 0xfe);//display  "AI icon

		 //display address 0xC4 -> temperature icon T7
		 TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber2_Low[lcd_t.number2_low]+lcdNumber3_High[lcd_t.number3_high])&0xff);//display "t,c"
		 
		 
	 	 }//don't Display numbers
		 else if(run_t.gTimer_numbers_one_two_blink > 5  && run_t.gTimer_numbers_one_two_blink <11){ //don't display 
            //display address 0xC2 -> 
	          if(run_t.gDry ==1 && run_t.gPlasma ==1  && run_t.gUltransonic==1)
			 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
	         else if(run_t.gDry ==0 && run_t.gPlasma ==1 && run_t.gUltransonic==1)
			 	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
	         else if(run_t.gDry ==0 && run_t.gPlasma ==0 && run_t.gUltransonic==1)
			 	TM1723_Write_Display_Data(0xC2,((0X01+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
			 else if(run_t.gDry ==0 && run_t.gPlasma ==0 && run_t.gUltransonic==0){
			 	TM1723_Write_Display_Data(0xC2,((0X01)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
			 }
			 else if(run_t.gDry ==1 && run_t.gPlasma ==1 && run_t.gUltransonic==0){
			 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
			 }
			 else if(run_t.gDry ==0 && run_t.gPlasma ==1 && run_t.gUltransonic==0){
			 	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
			 }
			 else if(run_t.gDry ==1 && run_t.gPlasma ==0 && run_t.gUltransonic==0){
			 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
			 }
			 else if(run_t.gDry ==1 && run_t.gPlasma ==0 && run_t.gUltransonic==1){
			 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0f);//display digital "temp
			 }
			 
				//TM1723_Write_Display_Data(0xC2,(((0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]) & 0x0F));
	           // display address 0xC3
	           if(run_t.gModel ==1)
			     TM1723_Write_Display_Data(0xC3,((lcdNumber1_Low[lcd_t.number1_low]+AI_Symbol+lcdNumber2_High[lcd_t.number2_high])) & 0x1);
	           else
			   	 TM1723_Write_Display_Data(0xC3,((lcdNumber1_Low[lcd_t.number1_low]+AI_NO_Symbol+lcdNumber2_High[lcd_t.number2_high])) & 0x0);
	           //display address 0xC4
				TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber2_Low[lcd_t.number2_low]+lcdNumber3_High[lcd_t.number3_high])&0xF1);//display "t,c"
        }
		else {
             run_t.gTimer_numbers_one_two_blink =0;
			 number_blink_times++;
		     if(number_blink_times > 2){
                 number_blink_times =0;
				 run_t.smart_phone_set_temp_value_flag =0;
                 gpro_t.set_temp_value_success = 1;
                 gpro_t.gTimer_temp_compare_value =20; //at once 
			}

		}
        TIM1723_Write_Cmd(LUM_VALUE);//(0x9B);
	 }
	 else{ //digital "1,2" don't blink LED

        if(disp_set_timer_value==1){

            disp_set_timer_value++;
          temp1 =   gpro_t.temp_real_value/ 10;
          temp2   = gpro_t.temp_real_value% 10;

           lcd_t.number1_low= temp1;
		   lcd_t.number1_high =temp1;

		   lcd_t.number2_low = temp2;
	       lcd_t.number2_high = temp2;


        }
	    //display address 0xC2 ->
	    Display_Kill_Dry_Ster_Icon();
		
		//display address 0xC3
		if(run_t.gModel==1){
	     TM1723_Write_Display_Data(0xC3,lcdNumber1_Low[lcd_t.number1_low]+AI_Symbol+lcdNumber2_High[lcd_t.number2_high]);//display  "AI icon"
		}
	   else { 
	 	TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[lcd_t.number1_low])+lcdNumber2_High[lcd_t.number2_high]);//don't display "AI icon"
		
	    }
	   
	   //display address 0xC4
        TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber2_Low[lcd_t.number2_low]+lcdNumber3_High[lcd_t.number3_high])&0xff);
	 }
	 
	 /**********************************end temperature*****************************************/
     //T2->"WIFI" icon -> 0xC5
     if(run_t.wifi_link_net_success ==0){   // && run_t.gPower_On==1){ //hasn't wifi run_t.wifi_link_net_success
         if(run_t.wifi_led_fast_blink_flag==0){
			 if(lcd_t.gTimer_wifi_500ms >99 && lcd_t.gTimer_wifi_500ms<200){
		          
		           TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[lcd_t.number3_low] + lcdNumber4_High[lcd_t.number4_high]) & 0xff); //Wifi
					
			 }
		     else if(lcd_t.gTimer_wifi_500ms <100){
			 	 
		         TM1723_Write_Display_Data(0xC5,(WIFI_NO_Symbol+lcdNumber3_Low[lcd_t.number3_low] + lcdNumber4_High[lcd_t.number4_high]) & 0xff); //Wifi 
	            
			 }
		     else{
		        lcd_t.gTimer_wifi_500ms =0;
		     }
         }
		 else{ //be detected of wifi signal fast blink wiif icon

             if(lcd_t.gTimer_wifi_500ms >14 && lcd_t.gTimer_wifi_500ms<30){ //400ms
		          
		           TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[lcd_t.number3_low] + lcdNumber4_High[lcd_t.number4_high]) & 0xff); //Wifi
					
			 }
		     else if(lcd_t.gTimer_wifi_500ms <15){
			 	 
		         TM1723_Write_Display_Data(0xC5,(WIFI_NO_Symbol+lcdNumber3_Low[lcd_t.number3_low] + lcdNumber4_High[lcd_t.number4_high]) & 0xff); //Wifi 
	            
			 }
		     else{
		        lcd_t.gTimer_wifi_500ms =0;
               
			 }
             if(run_t.gTimer_wifi_connect_counter > 120){ //
                  run_t.gTimer_wifi_connect_counter=0;
                  run_t.wifi_led_fast_blink_flag=0;
			      

			 }

		 }
		
     }
	 else if(run_t.wifi_link_net_success ==1){//wifi be connect is OK 
           run_t.wifi_led_fast_blink_flag=0;
           TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[lcd_t.number3_low] + lcdNumber4_High[lcd_t.number4_high]) & 0xff); //Wifi
         
	 }
	
	 TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);

}


/******************************************************************************
	*
	*Function Name:static void Display_Kill_Dry_Ster_Icon(void)
	*Function: display of icon , "1" -> ON ,"0"-> OFF
	*Input Ref:
	*Return Ref:
	*
******************************************************************************/
static void Display_Kill_Dry_Ster_Icon(void)
{

   //number "1,2" -> temperature

	  if(run_t.gDry==1 && run_t.gPlasma==1 && run_t.gUltransonic==1){

	     //display address 0xc2
	     TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high])&0xff);//display digital "temp
	     
		 
	  }
	  else if(run_t.gDry==0 && run_t.gPlasma==1 && run_t.gUltransonic==1){

	      TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_Symbol+BUG_Symbol))+lcdNumber1_High[lcd_t.number1_high]);//display digital "temp
	    
	   }
	   else if(run_t.gDry==0 && run_t.gPlasma==0 && run_t.gUltransonic ==1){

	        TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_NO_Symbol+BUG_Symbol))+lcdNumber1_High[lcd_t.number1_high]);//display digit
	        
	   }
	  else if(run_t.gDry==0 && run_t.gPlasma==0 && run_t.gUltransonic ==0){

	        TM1723_Write_Display_Data(0xC2,0X01+DRY_NO_Symbol+KILL_NO_Symbol+BUG_NO_Symbol+lcdNumber1_High[lcd_t.number1_high]);//display digit
	       
	  }
	  else if(run_t.gDry==1 && run_t.gPlasma==0 && run_t.gUltransonic ==1){

	        TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_NO_Symbol+BUG_Symbol))+lcdNumber1_High[lcd_t.number1_high]);//display digit
	       
	  }
	  else if(run_t.gDry==1 && run_t.gPlasma==0 && run_t.gUltransonic ==0){

	        TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_NO_Symbol+BUG_NO_Symbol))+lcdNumber1_High[lcd_t.number1_high]);//display digit
	       
	  }
	  else if(run_t.gDry==0 && run_t.gPlasma==1 && run_t.gUltransonic ==0){
	   
			  TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_Symbol+BUG_NO_Symbol))+lcdNumber1_High[lcd_t.number1_high]);//display digit
			  
	 }
	  else if(run_t.gDry==1 && run_t.gPlasma==1 && run_t.gUltransonic ==0){
		 
				TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_NO_Symbol))+lcdNumber1_High[lcd_t.number1_high]);//display digit
			
	   }

  
   TIM1723_Write_Cmd(LUM_VALUE);
   


}

/******************************************************************************
	*
	*Function Name:static void disp_fan_warning_time_colon_fun(void)
	*Function: 
	*Input Ref:
	*Return Ref:
	*
******************************************************************************/
#if 0
static void disp_fan_ptc_warning_time_colon_fun(void)
{
     if(lcd_t.gTimer_colon_ms < 6){
     	
		 	
	
		   TM1723_Write_Display_Data(0xCB,0x01+lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//display "r : 0"
	  
				 
	 }
	 else if(lcd_t.gTimer_colon_ms > 5 && lcd_t.gTimer_colon_ms < 11){
     	 
				TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//
			
				
				
        }
		else  lcd_t.gTimer_colon_ms = 0;



}
#endif 
/******************************************************************************
	*
	*Function Name:static void Display_Kill_Dry_Ster_Icon(void)
	*Function: display of icon , "1" -> ON ,"0"-> OFF
	*Input Ref:
	*Return Ref:
	*
******************************************************************************/
static void disp_fan_speed_level(void)
{

     if(run_t.disp_wind_speed_grade >66){
	 	TM1723_Write_Display_Data(0xCE,(T13+lcdNumber8_Low[lcd_t.number8_low]+ WIND_SPEED_FULL) & 0xff);
	  }
	  else if(run_t.disp_wind_speed_grade >33 && run_t.disp_wind_speed_grade <67){
	     TM1723_Write_Display_Data(0xCE,(T13+lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_TWO) & 0xff);

	  }
	  else if(run_t.disp_wind_speed_grade <34){
		 TM1723_Write_Display_Data(0xCE,(T13+lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_ONE) & 0xff);
	  }

}

/*************************************************************************************
    *
    *Function Name:static void donot_disp_T13_icon_fan_speed_level(void)
    *Function:
    *
    *
    *
**************************************************************************************/
static void donot_disp_T13_icon_fan_speed_level(void)
{
    if(run_t.disp_wind_speed_grade >66){
           TM1723_Write_Display_Data(0xCE,(lcdNumber8_Low[lcd_t.number8_low]+ WIND_SPEED_FULL) & 0xff);
         }
         else if(run_t.disp_wind_speed_grade >33 && run_t.disp_wind_speed_grade <67){
            TM1723_Write_Display_Data(0xCE,(lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_TWO) & 0xff);
    
         }
         else if(run_t.disp_wind_speed_grade <34){
            TM1723_Write_Display_Data(0xCE,(lcdNumber8_Low[lcd_t.number8_low]+WIND_SPEED_ONE) & 0xff);
         }
}
/*************************************************************************************
    *
    *Function Name:static void donot_disp_T13_icon_fan_speed_level(void)
    *Function:
    *
    *
    *
**************************************************************************************/
void disp_fan_leaf_run_icon(void)
{

   static uint8_t colon_flag_toggle;
   static uint8_t disp_flag_1,disp_1_default=0xff,disp_flag_2,disp_2_default=0xff;
  if(run_t.fan_warning ==0 &&  run_t.ptc_warning== 0)
  {

   
   if(lcd_t.gTimer_fan_10ms >39 && lcd_t.gTimer_fan_10ms<80){
  
        if(disp_1_default != disp_flag_1 ){
            disp_1_default = disp_flag_1;
            disp_flag_2++;
    
         works_timer_disp_numaber();

     

        TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[lcd_t.number4_low]+lcdNumber5_High[lcd_t.number5_high]) & 0xff);
        TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low[lcd_t.number5_low]+lcdNumber6_High[lcd_t.number6_high]);//display digital '5,6'
        if(colon_flag_toggle < 2){
                    colon_flag_toggle ++;
        TM1723_Write_Display_Data(0xCB,TIME_COLON+lcdNumber6_Low[lcd_t.number6_low]+lcdNumber7_High[lcd_t.number7_high]);//d
        }
        else{
        colon_flag_toggle=0;

        TM1723_Write_Display_Data(0xCB,TIME_NO_COLON+lcdNumber6_Low[lcd_t.number6_low]+lcdNumber7_High[lcd_t.number7_high]);//d


        }
        fan_disp_speed_leaf(0);

       }
    
    }
    else if(lcd_t.gTimer_fan_10ms <40){

     if(disp_2_default != disp_flag_2 ){
            disp_2_default = disp_flag_2;
            disp_flag_1++;
  

      works_timer_disp_numaber();

    
    TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[lcd_t.number4_low]+lcdNumber5_High[lcd_t.number5_high]) & 0xff);

    TM1723_Write_Display_Data(0xCA,lcdNumber5_Low[lcd_t.number5_low]+lcdNumber6_High[lcd_t.number6_high]);//display digit
    if(colon_flag_toggle ==0){
                   
      TM1723_Write_Display_Data(0xCB,TIME_COLON+lcdNumber6_Low[lcd_t.number6_low]+lcdNumber7_High[lcd_t.number7_high]);//d
     }
     else{
        

        TM1723_Write_Display_Data(0xCB,TIME_NO_COLON+lcdNumber6_Low[lcd_t.number6_low]+lcdNumber7_High[lcd_t.number7_high]);//d


     }
     fan_disp_speed_leaf(1);
      }
    }
    else if(lcd_t.gTimer_fan_10ms > 79){
        lcd_t.gTimer_fan_10ms=0;
        
    }


    }

}


static void works_timer_disp_numaber(void)
{
     switch(run_t.display_set_timer_or_works_mode){//switch(run_t.setup_timer_timing_item){

      case works_time:

      lcd_t.number5_low=(run_t.dispTime_hours ) /10;
     lcd_t.number5_high =lcd_t.number5_low;//(run_t.dispTime_hours) /10;

	 lcd_t.number6_low = (run_t.dispTime_hours ) %10;;
	 lcd_t.number6_high =  lcd_t.number6_low ;//(run_t.dispTime_hours ) %10;
     
     lcd_t.number7_low = (run_t.dispTime_minutes )/10;
	 lcd_t.number7_high = lcd_t.number7_low;//(run_t.dispTime_minutes )/10;

	 lcd_t.number8_low = (run_t.dispTime_minutes )%10;
	 lcd_t.number8_high = lcd_t.number8_low ;//(run_t.dispTime_minutes )%10;

      
    
    break;

    case setup_timer:
        
               lcd_t.number5_low=(run_t.timer_time_hours ) /10;
               lcd_t.number5_high =lcd_t.number5_low;//(run_t.timer_time_hours) /10;
    
               lcd_t.number6_low = (run_t.timer_time_hours ) %10;;
               lcd_t.number6_high =   lcd_t.number6_low;//(run_t.timer_time_hours ) %10;
    
               lcd_t.number7_low =0;
               lcd_t.number7_high = 0;
    
               lcd_t.number8_low = 0;
               lcd_t.number8_high = 0;


    break;


    case timer_time:
 

           lcd_t.number5_low=(run_t.timer_time_hours ) /10;
			lcd_t.number5_high =lcd_t.number5_low;//(run_t.timer_time_hours) /10;

			lcd_t.number6_low = (run_t.timer_time_hours ) %10;;
			lcd_t.number6_high = lcd_t.number6_low;//(run_t.timer_time_hours ) %10;

			lcd_t.number7_low = (run_t.timer_time_minutes )/10;
			lcd_t.number7_high =lcd_t.number7_low ;//(run_t.timer_time_minutes)/10;

			lcd_t.number8_low = (run_t.timer_time_minutes)%10;
			lcd_t.number8_high = lcd_t.number8_low ;//(run_t.timer_time_minutes )%10;


    break;

    

     }

}

void fan_disp_speed_leaf(uint8_t disp)
{

    if(disp==0){

      TM1723_Write_Display_Data(0xCC,T14_NO+lcdNumber7_Low[lcd_t.number7_low]+lcdNumber8_High[lcd_t.number8_high]);//display "7,8'
      disp_fan_speed_level();
      TM1723_Write_Display_Data(0xCF,((T11+T16)& 0x05));//

    }
    else{

       TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[lcd_t.number7_low]+lcdNumber8_High[lcd_t.number8_high]);//display "t,c
       donot_disp_T13_icon_fan_speed_level();
       TM1723_Write_Display_Data(0xCF,((T16+T12+T10)&0x0B));//

    }



}
/**********************************************************************************************************
*
*	Function Name: void power_off_disp_fan_run_handler(void)
*	Function:
*	Input Ref: NO
*	Return Ref: NO
*
**********************************************************************************************************/
void power_off_disp_fan_run_handler(void)
{
    if(lcd_t.gTimer_fan_10ms <40){

    
           TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[0x0A]+lcdNumber6_High[0x0A]) & 0xff);
           TM1723_Write_Display_Data(0xCB,(lcdNumber6_Low[0x0A]+lcdNumber7_High[0x0A]) & 0xff);
           TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[0x0A]+lcdNumber8_High[0x0A]) & 0xff);
          
           TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[0x0A]+WIND_SPEED_FULL);//display "t,c"
           TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
                    
         }
         else if(lcd_t.gTimer_fan_10ms >39 && lcd_t.gTimer_fan_10ms<80){ //close
                
     

         TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[0x0A]+lcdNumber6_High[0x0A]) & 0xff);

         TM1723_Write_Display_Data(0xCB,(lcdNumber6_Low[0x0A]+lcdNumber7_High[0x0A]) & 0xff);
         TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[0x0A]+lcdNumber8_High[0x0A]) & 0xff);
         TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[0x0A]+WIND_SPEED_FULL);//display "close"
        
         TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//
                  
    
         }
         else if(lcd_t.gTimer_fan_10ms > 79){
                lcd_t.gTimer_fan_10ms=0;
         }






}

