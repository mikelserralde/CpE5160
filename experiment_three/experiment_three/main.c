/*
 * experiment_three.c
 *
 * Created: 11/6/2020 6:00:58 PM
 *  Author: Hayden Long and Mikel Serralde
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "STA013.h"
#include "Control_Outputs.h"
#include "board.h"
#include "TWI.h"
#include "UART.h"
#include "UART_Print.h"

#define TWI_CLK_RATE 400000

int main()
{
	int8_t Starting_String[24] = "STA013 Config Starting\r\n";
	int8_t TWI_IN[17] = "TWI Initialized\r\n";
	int8_t Success_string[10] = "AAAAAAA!\r\n";
	uint8_t status;
		// Initialize RESET Pin
	Output_Init(&PB, PIN_B1);
	// Initialize DATA_REQ Pin
	Output_Init(&PC, PIN_C6);
	// Initialize BIT_EN Pin
	Output_Init(&PD, PIN_D6);

	UART_init(&UART1,9600);
	UART_Transmit_String(&UART1, 24, Starting_String);

	
	TWI_Init(&TWI1, TWI_CLK_RATE);
	UART_Transmit_String(&UART1, 24, TWI_IN);

	status = STA013_Config(&TWI1);
	if(status == 0xFF)
	{
		UART_Transmit_String(&UART1, 10, Success_string);

	}else
	{
			UART_Transmit_String(&UART1, 17, TWI_IN);
	}

    while (1) 
    {
		
    }
}

