#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


#define POWER_KEY_BIT_0	        (1 << 0)
#define MODE_KEY_1	        (1 << 1)
#define DEC_KEY_2           (1 << 2)
#define ADD_KEY_3           (1 << 3)

#define POWER_OFF_BIT_4        (1 << 4)
#define POWER_ON_BIT_5         (1<< 5)



#define MODE_LONG_KEY_8         (1 << 8)
#define DECODER_BIT_9          (1<< 9)


/***********************************************************************************************************
											函数声明
***********************************************************************************************************/
static void vTaskRunPro(void *pvParameters);
//static void vTaskDecoderPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);



/* 创建任务通信机制 */
//static void AppObjCreate(void);


/***********************************************************************************************************
											变量声明
***********************************************************************************************************/
static TaskHandle_t xHandleTaskRunPro = NULL;
//static TaskHandle_t xHandleTaskDecoderPro= NULL;
static TaskHandle_t xHandleTaskStart = NULL;

//static QueueHandle_t xQueue1 = NULL;
//static QueueHandle_t xQueue2 = NULL;
//static QueueHandle_t xQueue3 = NULL;



///#define QUEUE_LENGTH            1                   /* 队列支持的消息个敄1�7 */
///#define QUEUE_ITEM_SIZE         sizeof(uint32_t)    /* 队列中每条消息的大小 */
//#define SEMAPHORE_BINARY_LENGTH 1                   /* 二��信号量的有效长庄1�7 */
//#define QUEUESET_LENGTH         ((2 * QUEUE_LENGTH) + SEMAPHORE_BINARY_LENGTH)  /* 队列集支持的消息个数 */




typedef struct Msg
{
	uint8_t  ucMessageID;
	uint8_t  usData[12];
    uint8_t  long_key_mode_counter;
    uint8_t  key_long_mode_flag;
    //
    uint32_t  long_key_power_counter;
    uint8_t  key_long_power_flag;
	
}MSG_T;

MSG_T   gl_tMsg; /* 定义丢�个结构体用于消息队列 */

uint32_t mode_key_long_conter;

uint8_t  rx_end_counter,ulid,rx_data_counter,rx_end_flag;

uint8_t check_code;

uint8_t bcc_check_code;

 uint8_t dc_power_on_first ;




/**********************************************************************************************************
*	
*   Function Name:
*	Funciton:
*	Input Ref:
*   Return Ref:
*
**********************************************************************************************************/
void freeRTOS_Handler(void)
{
     /* 创建任务 */
	  AppTaskCreate();
	  
	  /* 创建任务通信机制 */
	 //  AppObjCreate();
	  
	  /* 启动调度，开始执行任劄1�71ￄ1�77 */
	   vTaskStartScheduler();


}
/**********************************************************************************************************
*	
*   Function Name:
*	Funciton: (数��越小优先级越低，这个跟uCOS相反) proritiy class is small and protity is low
*	Input Ref:
*   Return Ref:
*
**********************************************************************************************************/
static void vTaskRunPro(void *pvParameters)
{
    BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(20); /* 设置朢�大等待时间为30ms */
	uint32_t ulValue;
    
    static volatile uint8_t power_on_off_flag,fan_on_off_flag,dc_power_on ;
   
    static uint8_t smart_phone_app_power_on_flag,app_power_off_flag;
    while(1)
    {
		/*
			第一个参敄1�7 ulBitsToClearOnEntry的作用（函数执行前）＄1�7
		          ulNotifiedValue &= ~ulBitsToClearOnEntry
		          箢�单的说就是参数ulBitsToClearOnEntry那个位是1，那么notification value
		          的那个位就会被清零��1�7

		          这里ulBitsToClearOnEntry = 0x00000000就是函数执行前保留所有位〄1�7
		
		    第二个参敄1�7 ulBitsToClearOnExit的作用（函数逢�出前）：			
				  ulNotifiedValue &= ~ulBitsToClearOnExit
		          箢�单的说就是参数ulBitsToClearOnEntry那个位是1，那么notification value
		          的那个位就会被清零��1�7

				  这里ulBitsToClearOnExi = 0xFFFFFFFF就是函数逢�出前清楚扢�有位〄1�7
		
		    注：ulNotifiedValue表示任务vTaskMsgPro的任务控制块里面的变量��1�7		
		*/
		
		xResult = xTaskNotifyWait(0x00000000,      
						          0xFFFFFFFF,      
						          &ulValue,        /* 保存ulNotifiedValue到变量ulValue丄1�7 */
						          xMaxBlockTime);  /* 朢�大允许延迟时闄1�7 */
		
		if( xResult == pdPASS )
		{
			/* 接收到消息，棢�测那个位被按丄1�7 */




            if((ulValue & DECODER_BIT_9) != 0)
			{
        	 
              
                gpro_t.disp_rx_cmd_done_flag = 0;

             check_code =  bcc_check(gl_tMsg.usData,ulid);

             if(check_code == bcc_check_code ){
           
                receive_data_fromm_mainboard(gl_tMsg.usData);
                }
            }
            if((ulValue & POWER_KEY_BIT_0) != 0)
			{

                 gpro_t.key_power_flag = 1;
                 gl_tMsg.key_long_power_flag=0;
                 gl_tMsg.long_key_power_counter=0;
              
            }
            else if((ulValue & POWER_ON_BIT_5) != 0){

                    smart_phone_app_power_on_flag=1;

            }
             else if((ulValue & POWER_OFF_BIT_4) != 0){

                    app_power_off_flag =1;

            }
           
           
    }
    else{

        if( gpro_t.key_power_flag == 1){

            if(KEY_POWER_GetValue()  ==KEY_UP){
                gpro_t.key_power_flag++;
              

             if(gl_tMsg.key_long_power_flag ==1){
                  power_key_long_fun();
                  SendData_Set_Command(0x05,0x01); // link wifi of command .
                  gpro_t.gTimer_mode_key_long=0;


             }
             else{
             if(run_t.gPower_On == power_off){
                run_t.gPower_On = power_on;
                gl_tMsg.long_key_power_counter =0;
               
                SendData_PowerOnOff(1);
                power_on_key_short_fun();
                gpro_t.gTimer_mode_key_long=0;

              }
              else{

                 run_t.gPower_On = power_off;

              }

              }
             }

            }
            else if(smart_phone_app_power_on_flag ==1){
                smart_phone_app_power_on_flag++;
                 run_t.gPower_On = power_on;
                gl_tMsg.long_key_power_counter =0;
                
                power_on_key_short_fun();

            }
            else if(app_power_off_flag ==1){
                app_power_off_flag++;

                run_t.gPower_On = power_off;
            }
            else if(gpro_t.key_mode_flag == 1 && run_t.gPower_On == power_on){

                 if(KEY_MODE_GetValue() == KEY_UP){
                  
                      gpro_t.key_mode_flag++;
                     if(gl_tMsg.key_long_mode_flag==0){//
                           gl_tMsg.long_key_mode_counter=0;
                            //SendData_Buzzer();
                            //osDelay(5);
                    
                            //mode_key_short_fun();

                      }
                      else{
                       gpro_t.gTimer_mode_key_long=0;

                       mode_key_long_fun();
                        
                

                      }

                 }
            }
            else if((gpro_t.key_add_flag ==1 || gpro_t.key_dec_flag ==1)&&run_t.gPower_On == power_on){
                

              if(gpro_t.key_add_flag == 1){

                 
               if(KEY_ADD_GetValue() == KEY_UP){
                  gpro_t.key_add_flag ++;
                  
                   SendData_Buzzer();
                   osDelay(5);
                
                  add_key_fun();
                }
              

              }
              else if(gpro_t.key_dec_flag == 1){
               
                if(KEY_DEC_GetValue()==KEY_UP){
                    gpro_t.key_dec_flag ++;
                   SendData_Buzzer();
                   osDelay(5);
                
                   dec_key_fun();
                }
            } 
        }

      
          
          
      if(run_t.gPower_On == power_on){

           if(gpro_t.key_mode_flag==2 && gl_tMsg.key_long_mode_flag ==0){
             gpro_t.key_mode_flag++;
             SendData_Buzzer();
             HAL_Delay(10);
             mode_key_short_fun();


            }



            if( gpro_t.gTimer_mode_key_long > 1 && (gl_tMsg.key_long_mode_flag  ==1 ||gl_tMsg.key_long_power_flag ==1)){
               

                  gl_tMsg.long_key_mode_counter =0;
                 gl_tMsg.long_key_power_counter =0;
                if(gl_tMsg.key_long_power_flag ==1){

                    gl_tMsg.key_long_power_flag=0;
                }
                if(gl_tMsg.key_long_mode_flag==1){
                    gl_tMsg.key_long_mode_flag=0;

                 }

            }

         
            
            
       set_temperature_compare_value_fun();
            
       disp_temp_humidity_wifi_icon_handler();

       display_timer_and_beijing_time_handler();

       disp_time_colon_ion_handler();

       Timing_Handler();

       }
       else if(run_t.gPower_On == power_off){

          power_off_handler();

       }
      //USART1_Cmd_Error_Handler();

    }

   }
}
/**********************************************************************************************************
*	凄1�71ￄ1�77 敄1�71ￄ1�77 各1�71ￄ1�77: vTaskStart
*	功能说明: 消息处理，使用函数comGetChar获取串口命令，使用函数comSendBuf发��串口消恄1�71ￄ1�77
*	彄1�71ￄ1�77    叄1�71ￄ1�77: pvParameters 是在创建该任务时传��的形参
*	迄1�71ￄ1�77 囄1�71ￄ1�77 倄1�71ￄ1�77: 旄1�71ￄ1�77
*   伄1�71ￄ1�77 兄1�71ￄ1�77 纄1�71ￄ1�77: 3  (数��越小优先级越低，这个跟uCOS相反)
**********************************************************************************************************/
static void vTaskStart(void *pvParameters)
{

   while(1)
    {
      
    if(KEY_POWER_GetValue()  ==KEY_DOWN){

       
             gl_tMsg.long_key_mode_counter =0;
            gl_tMsg.long_key_power_counter++;

         if(gl_tMsg.long_key_power_counter > 15 && run_t.gPower_On == power_on ){
            gl_tMsg.long_key_power_counter =0;
            gl_tMsg.key_long_power_flag =1;
             gpro_t.gTimer_mode_key_long = 0;
            
             SendData_Buzzer();
         }

        if(dc_power_on_first==0){

          dc_power_on_first++;

        }
        else{
            gpro_t.key_power_flag = 1;

        }

     }
     else if(KEY_MODE_GetValue() ==KEY_DOWN){

           gl_tMsg.long_key_power_counter=0;
         
          gl_tMsg.long_key_mode_counter ++ ;

          if(gl_tMsg.long_key_mode_counter > 15  && run_t.gPower_On == power_on &&  run_t.ptc_warning ==0 && run_t.fan_warning ==0){
             gl_tMsg.long_key_mode_counter=0;   
         
             gl_tMsg.key_long_mode_flag =1;
               gpro_t.gTimer_mode_key_long = 0;
            
                SendData_Buzzer();
           }


         gpro_t.key_mode_flag  =  1;


     }
     else if(KEY_DEC_GetValue() == KEY_DOWN){


            gl_tMsg.long_key_power_counter=0;
         
          gl_tMsg.long_key_mode_counter =0 ;
               gpro_t.key_dec_flag = 1;
     }
     else if(KEY_ADD_GetValue() ==KEY_DOWN){

          gl_tMsg.long_key_power_counter=0;
         
          gl_tMsg.long_key_mode_counter =0 ;
         gpro_t.key_add_flag = 1;

    }
    vTaskDelay(30);
     
    }

}
/**********************************************************************************************************
*	凄1�71ￄ1�77 敄1�71ￄ1�77 各1�71ￄ1�77: AppTaskCreate
*	功能说明: 创建应用任务
*	彄1�71ￄ1�77    参：旄1�71ￄ1�77
*	迄1�71ￄ1�77 囄1�71ￄ1�77 倄1�71ￄ1�77: 旄1�71ￄ1�77
**********************************************************************************************************/
void AppTaskCreate (void)
{

	xTaskCreate( vTaskRunPro,    		/* 任务函数  */
                 "vTaskRunPro",  		/* 任务各1�71ￄ1�77    */
                 256,         		/* stack大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 1,           		/* 任务优先纄1�71ￄ1�77 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskRunPro); /* 任务句柄  */

  
    #if 0
    xTaskCreate( vTaskDecoderPro,     		/* 任务函数  */
                 "vTaskDecoderPro",   		/* 任务各1�71ￄ1�77    */
                 128,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 2,               		/* 任务优先纄1�71ￄ1�77 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskDecoderPro );  /* 任务句柄  */
   
	#endif 
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务各1�71ￄ1�77    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 2,              		/* 任务优先纄1�71ￄ1�77 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskStart );   /* 任务句柄  */
}

/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
     static uint8_t state;
     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    


    if(huart==&huart1) // Motor Board receive data (filter)
	{

    //   DISABLE_INT();
       switch(state)
		{
		case 0:  //#0
			if(inputBuf[0] == 0x5A){  // 0x5A --main board singla
               rx_data_counter=0;
               gl_tMsg.usData[rx_data_counter] = inputBuf[0];
				state=1; //=1

             }
            else
                state=0;
		break;

       
		case 1: //#1

            if(gpro_t.disp_rx_cmd_done_flag ==0){
              /* 初始化结构体指针 */
               rx_data_counter++;
		     
	          gl_tMsg.usData[rx_data_counter] = inputBuf[0];
              

              if(rx_end_flag == 1){

                state = 0;
            
                ulid = rx_data_counter;
                rx_end_flag=0;

                rx_data_counter =0;

                gpro_t.disp_rx_cmd_done_flag = 1 ;

         

                bcc_check_code=inputBuf[0];

              
                xTaskNotifyFromISR(xHandleTaskRunPro,  /* 目标任务 */
                DECODER_BIT_9,     /* 设置目标任务事件标志位bit0  */
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
                &xHigherPriorityTaskWoken);

                /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
                  
              }

              }

              if(gl_tMsg.usData[rx_data_counter] ==0xFE && rx_end_flag == 0 &&  rx_data_counter > 4){
                     
                          rx_end_flag = 1 ;
                          
                        
               }

        break;


			
		}
     //   ENABLE_INT();
       __HAL_UART_CLEAR_OREFLAG(&huart1);
		HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
	}
}

#if 0
void USART1_Cmd_Error_Handler(void)
{
   uint32_t temp;
   if(run_t.gTimer_usart_error >4){
	  	run_t.gTimer_usart_error=0;
	    
         
        __HAL_UART_CLEAR_OREFLAG(&huart1);
        temp = USART1->RDR;
		UART_Start_Receive_IT(&huart1,inputBuf,1);
       
		}
      
    
  
 }

#endif 


/****************************************************************************
 * 
 * Function Name: void App_PowerOnOff_Handler(void)
 * Function:
 * Input Ref: NO
 * Return Ref: NO
 * 
*****************************************************************************/
void App_PowerOff_Handler(void)
{
     
     xTaskNotify(xHandleTaskRunPro, /* 目标任务 */
	 POWER_OFF_BIT_4 ,            /* 设置目标任务事件标志位bit0  */
	 eSetBits);             /* 将目标任务的事件标志位与BIT_0进行或操作，  将结果赋值给事件标志位。*/
     

}

void App_PowerOn_Handler(void)
{
     
     xTaskNotify(xHandleTaskRunPro, /* 目标任务 */
	 POWER_KEY_BIT_0 ,            /* 设置目标任务事件标志位bit0  */
	 eSetBits);             /* 将目标任务的事件标志位与BIT_0进行或操作，  将结果赋值给事件标志位。*/
     

}

















