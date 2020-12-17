/*
 * FAT File System
 *
 * Created: 7/2/2020 1:57:23 PM
 * Author : youngerr
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "Control_Outputs.h"
#include "UART.h"
#include "UART_Print.h"
#include "SPI.h"
#include "SDCard.h"
#include "Long_Serial_In.h"
#include "board.h"
#include "print_memory.h"
#include <avr/pgmspace.h>
#include "Directory_Functions_struct.h"
#include "File_System_v2.h"
#include "I2C.h"
#include "STA013_Config.h"

const char LSI_Prompt[16] PROGMEM = {"Enter block #: "};

uint8_t buffer1[512];
uint8_t buffer2[512];

int main(void)
{
    /* Replace with your application code */
	uint8_t *prnt_bffr;
	uint32_t temp32;
	
	uint16_t temp16, num_entries, entry_num;
	uint32_t Current_directory, Entry_clus;
	FS_values_t * Drive_p;

	prnt_bffr=Export_print_buffer();
	Output_Set(&PA,(LED3|OLED_C_D));
	Output_Init(&PA,(LED3|OLED_C_D));
	Output_Set(&PB,(SD_CS|LED1|OLED_CS));
	Output_Init(&PB,(SD_CS|LED1|OLED_CS));
	//Output_Set(&PC,(USER_LED));
	//Output_Init(&PC,(USER_LED));
	Output_Set(&PC,(0b10000000));
	Output_Init(&PC,(0b10000000));
	Output_Set(&PE,(LED2));
	Output_Init(&PE,(LED2));
	
	SPI_Master_Init(&SPI0,400000);
	//OLED_Init();
	UART_init(&UART1,9600);
	SD_Card_Init();
	SPI_Master_Init(&SPI0,2000000);
	
	TWI_Master_Init(&TWI1,25000);
	STA013_Init();
	
	Mount_Drive(buffer1);
	Drive_p=Export_Drive_values();
	Current_directory=Drive_p->FirstRootDirSec;
    while (1) 
    {
		 sprintf(prnt_bffr,"Directory Sector = %lu\n\r",Current_directory);
		 UART_Transmit_String(&UART1,0,prnt_bffr);
		 num_entries=Print_Directory(Current_directory, buffer1);
		 sprintf(prnt_bffr,"Enter Selection = ");
		 UART_Transmit_String(&UART1,0,prnt_bffr);
		 entry_num=(uint16_t)long_serial_input(&UART1);
		 if(entry_num<=num_entries)
		 {
			 Entry_clus=Read_Dir_Entry(Current_directory, entry_num, buffer1);
			 if((Entry_clus&directory_bit)==directory_bit)
			 {
				 Entry_clus&=0x0FFFFFFF;
				 Current_directory=First_Sector(Entry_clus);
			 }
			 else
			 {
				 //Open_File(Entry_clus, buffer1);
				 Play_MP3_File(Entry_clus);
			 }
			 
		 }
		 else
		 {
			 sprintf(prnt_bffr,"Invalid Selection\n\r");
			 UART_Transmit_String(&UART1,0,prnt_bffr);
		 }
		 
		 /*Copy_String_to_Buffer(LSI_Prompt,0,prnt_bffr);
		 UART_Transmit_String(&UART1,0,prnt_bffr);
		 temp32=long_serial_input(&UART1);
		 Output_Clear(&PB,LED1);
		 Output_Clear(&PB,SD_CS);  // Clear nCS = 0
		 Send_Command(17,temp32);
		 Read_Block(512,buffer1);
		 Output_Set(&PB,LED1);
		 Output_Set(&PB,SD_CS);  // Set nCS = 1
		 print_memory(&UART1,512,buffer1); */
		 
    }
}

