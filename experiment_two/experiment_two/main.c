/*
main.c
Description: 
Created by Hayden Long and Mikel Serralde 10/20/2020
*/

#include <avr/io.h>
#include <stdint.h>
#include "board.h"
#include "UART.h"
#include "UART_Print.h"
#include "SPI.h"
#include "Control_Outputs.h"
#include "Long_Serial_In.h"
#include "sdcard.h"
#include "print_memory.h"


#define SPI_FREQ_SD_INIT 400000


int main()
{
	uint8_t SD_Status;
	uint32_t selected_sd_block;
	uint8_t data[512];
	int8_t SD_Fail_String[22] = "SD CARD INIT FAILED.\r\n"; 
	int8_t SD_SUCCESS_String[35] = "SD CARD INITIALIZED SUCCESSFULLY!\r\n";
	int8_t USER_PROMPT[26] = "\r\nINPUT DESIRED SD BLOCK: ";
	int8_t POST_PROMPT[2] = "\r\n";
	int8_t SD_ReadBlock_String[27] = "SD CARD READ BLOCK ERROR.\r\n";

	UART_init(&UART1,9600);

	SPI_Master_Init(&SPI0, SPI_FREQ_SD_INIT);

	SD_Status = SD_Card_Init();

	if(SD_Status != SUCCESS)
	{
		UART_Transmit_String(&UART1, 22, SD_Fail_String);
		while(1)
		{
			// Ends Program
			
		}
	}

	UART_Transmit_String(&UART1, 35, SD_SUCCESS_String);
		
	while(1)
	{
		// super loop, one loop one equation
		
		// Prompt User
		UART_Transmit_String(&UART1, 26, USER_PROMPT);
		selected_sd_block = long_serial_input(&UART1);
		UART_Transmit_String(&UART1, 2, POST_PROMPT);
		
		// Clear /CS
		Output_Clear(&PB, (SD_CS));
		
		// Select Data Block
		if(Send_Command(CMD17, selected_sd_block) != SUCCESS)
		{
			while(1)
			{
				// Ends Program
			}
		}
		
		// Read Data Block
		if(Read_Block(512, data) != SUCCESS)
		{
			UART_Transmit_String(&UART1, 27, SD_ReadBlock_String);
			while(1)
			{
				// Ends Program
			}
		}
		// Set /CS = 1
		Output_Set(&PB, (SD_CS));
		
		print_memory(&UART1, 512, data);
		
	}
	return 0;
}



