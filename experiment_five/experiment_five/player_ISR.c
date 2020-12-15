#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "board.h"
#include "player_ISR.h"
#include "SPI.h"
#include "SDCard.h"
#include "File_System_v2.h"
#include "Directory_Functions_struct.h"
#include "Read_Sector.h"
#include "Control_Outputs.h"
#include "Read_Inputs.h"
#include "Timer_Interrupt_Init.h"
#include "Hardware_Timeout.h"


extern uint8_t buffer1[512];
extern uint8_t buffer2[512];


uint8_t volatile play_status_g;
uint8_t num_sectors_g, LCD_update_flag;
uint8_t LCD_Time_g[4]; // MM:SS are elements 01:23
uint16_t index1_g, index2_g, msecs_g;
uint32_t sector_g, cluster_g;


play_state_t play_state_g;

/***********************************************************************
DESC:    Initializes and starts Timer0 for a hardware delay for 
         creating a consistent I2C frequency
RETURNS: nothing
CAUTION: 
          
************************************************************************/



ISR(TIMER2_COMPA_vect)
{
   FS_values_t * Drive_p;
   uint8_t timeout, DR_input, buffer_flag;

   Drive_p=Export_Drive_values();
   switch(play_state_g)
   {
     case data_idle_1:
     {
        DR_input=Read_Pin(&PC,DATA_REQ);
		if(DR_input==0)
	    {
	      play_state_g=send_data_1;
	    }
        break;
     }
    case send_data_1:
     {
       buffer_flag=0;
	   DR_input=Read_Pin(&PC,DATA_REQ);
  
  
  
  
	  break;
	 }

    }   
}


void Play_MP3_file(uint32_t begin_cluster)
{
   FS_values_t * Drive_p;

   Drive_p=Export_Drive_values();
   //**** LEDS initialized for debugging ****//
   Output_Set(&PA,(LED3));
   Output_Init(&PA,(LED3));
   Output_Set(&PB,(LED1));
   Output_Init(&PB,(LED1));
   Output_Set(&PC,(USER_LED));
   Output_Init(&PC,(USER_LED));
   Output_Set(&PE,(LED2));
   Output_Init(&PE,(LED2));
   Output_Clear(&PD,(BIT_EN));
   Output_Init(&PD,(BIT_EN));
   Pull_Up_Enable(&PC,(DATA_REQ));
   Input_Init(&PC,(DATA_REQ));
   
   
   cluster_g=begin_cluster;
   sector_g=First_Sector(begin_cluster);
   num_sectors_g=0;
   for(index1_g=0;index1_g<512;index1_g++)
   {
     buffer1[index1_g]=0;  
   }
   index1_g=0;
   for(index2_g=0;index2_g<512;index2_g++)
   {
     buffer2[index2_g]=0;
   }
   index2_g=0;
   Read_Sector((sector_g+num_sectors_g), (Drive_p->BytesPerSec),buffer1);
   num_sectors_g++;
   index1_g=0;
   Read_Sector((sector_g+num_sectors_g), (Drive_p->BytesPerSec),buffer2);
   num_sectors_g++;
   index2_g=0;
   play_state_g=send_data_1;
   play_status_g=1;
   Timer2_Interrupt_Init(MP3_timeout_ms);
   sei();
   //set_sleep_mode(SLEEP_MODE_IDLE);
   while(play_status_g!=0)
   {
     //sleep_mode();  //Go to Sleep
   }
   cli();
}




  
 




