#include "board.h"
#include "I2C.h"
#include "STA013_Config.h"
#include <stdio.h>
#include "UART.h"
#include "UART_Print.h"
#include <avr/pgmspace.h>
#include "Control_Outputs.h"

extern const uint8_t CONFIG[3998];
extern const uint8_t CONFIG2[50];

void STA013_Reset_Init(void)
{
	//Set Port B, Pin 3 to be an output with initial value 1
	DDRB|=(1<<1);
	PORTB|=(1<<1);
}

void STA013_Reset_Control(uint8_t control)
{
	//control = 1, STA013_Reset=1; control = 0, STA013_Reset=0
	if(control==1)
	{
		PORTB|=(1<<1);    // LED off
	}
	else
	{
		PORTB&=(~(1<<1));   // LED on
	}
}

void STA013_BIT_EN_Init(void)
{
	//Set Port B, Pin 3 to be an output with initial value 1
	DDRD|=(1<<6);
	PORTD&=(~(1<<6));
}

void STA013_BIT_EN_Control(uint8_t control)
{
	//control = 1, SD_Select=1; control = 0, SD_Select=0
	if(control==1)
	{
		PORTD|=(1<<6);    // LED off
	}
	else
	{
		PORTD&=(~(1<<6));   // LED on
	}
}

void STA013_DATA_REQ_Init(void)
{
	//Set Port C, Pin 6 to be an input with pull-up disabled
	DDRC&=(~(1<<6));
	PORTC&=(~(1<<6));
}

/***********************************************************************
DESC:    Initializes the STA013 with the following steps:
         Applies a hardware reset signal, checks the ID register for an 0xAC
		 response and then sends the configuration data.
RETURNS: error flag
CAUTION: 
          
************************************************************************/
const uint8_t STA_cfg_addr[18] PROGMEM = {0x54, 0x55,  6, 11,  82,  81, 101, 100, 80, 97, 0x05, 0x0d, 0x18, 0x0c, 0x46, 0x48, 0x7d, 0x72};
const uint8_t STA_cfg_data[18] PROGMEM = {0x07, 0x10,  9,  2, 184,   0,   0,   0,  6,  5, 0xa1, 0x00, 0x04, 0x05, 0x07, 0x07, 0x00, 0x01};

const char Error_prnt[13] PROGMEM = {"error flag: "};
const char ID_Reg_prnt[26] PROGMEM = {"Output from ID register: "};
const char STA_Ver_prnt[21] PROGMEM = {"STA013 SoftVersion: "};
const char First_config_prnt[35] PROGMEM = {"First configuration file sent...\n\r"};
const char Number_written_prnt[27] PROGMEM = {"Number of values written: "};
const char STA_sent_prnt[17] PROGMEM = {"Sent to STA013: "};
const char STA_rec_prnt[21] PROGMEM = {"Output from STA013: "};
const char Config_Complete_prnt[25] PROGMEM = {"Configuration Complete\n\r"};
	
uint8_t STA013_Init(void)
{
   uint8_t error_flag, timeout, length, reg_addr;
   uint8_t send[2], rcv[2];
   uint16_t j;
   char * prnt_bffr;
   
   
   //STA013_RESET=0;
   //STA013_Reset_Control(0);
   Output_Clear(&PB,(1<<1));
   Output_Init(&PB,(1<<1));
   //send[0]=0x01;   // address of the ID reg.  
   timeout=50;
   prnt_bffr=Export_print_buffer();
   //STA013_RESET=1;    // make STA013 active
   //STA013_Reset_Control(1);
   Output_Set(&PB,(1<<1));
   /*do
   {
      error_flag=I2C_Write(STA013,1,send);
      timeout--;
      if(timeout==0) 
	  {
		  PORTLED &= ~(1 << PORTLED_AMBER);
		  length = Copy_String_to_Buffer(Error_prnt,prnt_bffr);
		  sprintf((prnt_bffr+(length-1)), "%2.2X \n\r",error_flag);
		  UART1_Transmit_String(0,prnt_bffr);
	  }
   }while((error_flag!=no_errors)&&(timeout!=0)); */
      timeout=50;
	  do
	  {
        error_flag=TWI_Master_Receive(&TWI1,STA013,1,1,1,rcv);
        timeout--;
	  }while((error_flag!=no_errors)&&(timeout!=0));
	  //send[0]='I';
	  //send[1]='2';
	  //send[2]='C';
	  //LCD_Print(3,send);
	  if(timeout!=0)
	  {
         length = Copy_String_to_Buffer(ID_Reg_prnt,0,prnt_bffr);
         sprintf((prnt_bffr+(length-1)), "%2.2X \n\r",rcv[0]);
		 //sprintf(prnt_bffr, "Output from ID register: %2.2X \n\r",rcv[0]);
		 UART_Transmit_String(&UART1,0,prnt_bffr);
	  }
	  else
	  {
		  length = Copy_String_to_Buffer(Error_prnt,0,prnt_bffr);
		  sprintf((prnt_bffr+(length-1)), "%2.2X \n\r",error_flag);
		  UART_Transmit_String(&UART1,0,prnt_bffr);
	  } 
   

   //LED1_Control(1);
   Output_Set(&PB,LED1);
   //rcv[0]=0xAC;
   if(rcv[0]==0xAC)
   {
     /*send[0]=0x71;
     error_flag=I2C_Write(STA013,1,send);
     error_flag=I2C_Read(STA013,1,rcv);
	 length = Copy_String_to_Buffer(STA_Ver_prnt,prnt_bffr);
	 sprintf((prnt_bffr+(length-1)), "%2.2X \n\r",rcv[0]);
     //sprintf(prnt_bffr, "STA013 SoftVersion: %2.2X \n\r",rcv[0]); 
	 UART1_Transmit_String(0,prnt_bffr); */
     j=0;
     do
     {
        reg_addr=pgm_read_byte(&CONFIG[j]);
        j++;
        send[0]=pgm_read_byte(&CONFIG[j]);
        j++;
        if(reg_addr!=0xff)
        {
          
           timeout=50;
           do
           {
               error_flag=TWI_Master_Transmit(&TWI1,STA013,reg_addr,1,1,send);
               timeout--;
               if(timeout==0)
			   {
				    Output_Set(&PC,USER_LED);
					sprintf(prnt_bffr,"%u\n\r",error_flag);
					UART_Transmit_String(&UART1,0,prnt_bffr);
			   }
           }while((error_flag!=no_errors)&&(timeout!=0));
        }
     }while((reg_addr!=0xff) && (timeout!=0));
	 Copy_String_to_Buffer(First_config_prnt,0,prnt_bffr);
     //sprintf(prnt_bffr, "First configuration file sent...\n\r");
	 UART_Transmit_String(&UART1,0,prnt_bffr);
	 length = Copy_String_to_Buffer(Number_written_prnt,0,prnt_bffr);
	 sprintf((prnt_bffr+(length-1)), "%2.2X \n\r",j>>1);
     //sprintf(prnt_bffr, "Number of values written: %d \n\r",j>>1);
	 UART_Transmit_String(&UART1,0,prnt_bffr);
	 //LED2_Control(1); 
	 Output_Set(&PE,LED2);
     j=0;
     
     do
     {
        reg_addr=pgm_read_byte(&CONFIG2[j]);
        j++;
        send[0]=pgm_read_byte(&CONFIG2[j]);
        j++;
        if(reg_addr!=0xff)
        {
           timeout=50;
           do
           {
               error_flag=TWI_Master_Transmit(&TWI1,STA013,reg_addr,1,1,send);
               timeout--;
               //if(timeout==0) PORTLED &= ~(1 << PORTLED_AMBER);
           }while((error_flag!=no_errors)&&(timeout!=0));
        }
     }while((reg_addr!=0xff) && (timeout!=0) && (error_flag==no_errors));
     /*send[0]=0x71;
     error_flag=I2C_Write(STA013,1,send);
     error_flag=I2C_Read(STA013,1,rcv);
	 
     length = Copy_String_to_Buffer(STA_Ver_prnt,prnt_bffr);
     sprintf((prnt_bffr+(length-1)), "%2.2X \n\r",rcv[0]);
	 //sprintf(prnt_bffr, "STA013 SoftVersion: %2.2X \n\r",rcv[0]);   
	 UART1_Transmit_String(0,prnt_bffr); */         
     //LED3_Control(1); 
	 Output_Set(&PA,LED3); 
     for(j=0;j<18;j++)
	  {
	    reg_addr=pgm_read_byte(&STA_cfg_addr[j]);
	    send[0]=pgm_read_byte(&STA_cfg_data[j]);
        timeout=50;
        do
        {
            error_flag=TWI_Master_Transmit(&TWI1,STA013,reg_addr,1,1,send);
            timeout--;
            if(timeout==0) Output_Set(&PC,USER_LED);
        }while((error_flag!=no_errors)&&(timeout!=0));
		length = Copy_String_to_Buffer(STA_sent_prnt,0,prnt_bffr);
		sprintf((prnt_bffr+(length-1)), "%2.2X  %2.2X \n\r",reg_addr,send[0]);
		//sprintf(prnt_bffr, "Sent to STA013: %2.2X  %2.2X \n\r",send[0],send[1]);
		UART_Transmit_String(&UART1,0,prnt_bffr);
        //error_flag=I2C_Write(STA013,1,send);
        //error_flag=I2C_Read(STA013,1,rcv);
		error_flag=TWI_Master_Receive(&TWI1,STA013,reg_addr,1,1,rcv);
		length = Copy_String_to_Buffer(STA_rec_prnt,0,prnt_bffr);
		sprintf((prnt_bffr+(length-1)), "%2.2X  %2.2X %2.2X \n\r",reg_addr,rcv[0],error_flag);
        //sprintf(prnt_bffr, "Output from register: %2.2X  %2.2X %2.2X \n\r",send[0],rcv[0],error_flag);
		UART_Transmit_String(&UART1,0,prnt_bffr);
	  }
	  Copy_String_to_Buffer(Config_Complete_prnt,0,prnt_bffr);
      //sprintf(prnt_bffr, "Configuration Complete\n\r");
	  UART_Transmit_String(&UART1,0,prnt_bffr);
   }   
   //LED1_Control(0);
   Output_Clear(&PB,LED1);
   //LED2_Control(0);
   Output_Clear(&PE,LED2);
   //LED3_Control(0); 
   Output_Clear(&PA,LED3);  
   return error_flag;
}
