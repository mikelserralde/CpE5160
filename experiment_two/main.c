/*
main.c
Description: 
Created by Hayden Long and Mikel Serralde 10/20/2020
*/
#include <stdio.h>
#include "board.h"
#include "SPI.h"
#include "Control_Outputs.h"
#include "sdcard.h"


#define SPI_FREQ_SD_INIT 400000


void main()
{
	uint8_t SD_Status;
	uint32_t selected_sd_block;
	uint8_t data[512];
	
	SPI_Master_Init(&SPI0, SPI_FREQ_SD_INIT);
	SD_Status = SD_Card_Init();
	UART_init(&UART1,9600);
	
	
	while(1)
	{
		
		// super loop, one loop one equation
		// Prompt User
		selected_sd_block = long_serial_input(&UART1);
		if(Send_Command(CMD17, 0UL) != 0xFF)
		{
			while(1)
			{
				// Ends Program
			}
		}
		
		// Where do we input the # for the data block????????? @younger
		if(Read_Block(512, data) != 0xFF)
		{
			while(1)
			{
				// Ends Program
			}
		}
		
		
	}
	return 0;
}



