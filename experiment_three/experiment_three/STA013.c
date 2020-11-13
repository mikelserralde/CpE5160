/*
 * STA013.c
 *
 * Created: 11/11/2020 
 *  Author: Hayden Long and Mikel Serralde
 */ 

#include "STA013.h" 
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdio.h>
#include "UART.h"
#include "UART_Print.h"
#include "Control_Outputs.h"
#include "board.h"
#include "TWI.h"
#include <util/delay.h>



// Import the labels 
extern const uint8_t *CONFIG;
extern const uint8_t *CONFIG2;
extern const uint8_t *CONFIG3;

uint8_t STA013_Config(uint8_t volatile* TWI_addr) //??? Definitely not what the function is supposed to be
{
	int8_t Starting_String[24] = "STA013 Config contuing\r\n";
	// Read 0xAC from ID register
	uint8_t timeout = 0;
	uint8_t index = 0;
	uint8_t status;
	uint8_t receive_array[3];
	uint8_t send_array[2];
	int8_t prnt_bffr[64];
	
	// Clear RESET then wait 1 ms
	Output_Clear(&PB, PIN_B1);
	_delay_ms(1);
	// Set Reset
	Output_Set(&PB, PIN_B1);

	// Clear BIT_EN, no data being sent on SPI
	Output_Clear(&PD, PIN_D6);

	// Set DATA_REQ to receive data from STA013
	Output_Set(&PC, PIN_C6);

	do
	{
		status = TWI_Master_Receive(TWI_addr, 0x43, 3, receive_array);
		timeout++;
	}while((timeout<50) && (status != SUCCESS));
	sprintf(prnt_bffr, "Received Value = %2.2X\n\r", receive_array[2]);
	UART_Transmit_String(&UART1,0,prnt_bffr);
	if(status != SUCCESS)
	{
		UART_Transmit_String(&UART1,0,prnt_bffr);
	}
	
	do
	{
		send_array[0] = pgm_read_byte(&CONFIG[index]);
		index++;
		send_array[1] = pgm_read_byte(&CONFIG[index]);
		index++;
		timeout = 0;
		UART_Transmit_String(&UART1, 24, Starting_String);
		do{
			status = TWI_Master_Transmit(TWI_addr, 0x43,2, send_array);
			timeout++;
		}while((status != SUCCESS) && (timeout < 50));
	}while((send_array[0] != 0xFF) && (timeout < 50));

	if(timeout< 50)
	{
		sprintf(prnt_bffr,"Config 1 sent...\n\r");
		UART_Transmit_String(&UART1, 0, prnt_bffr);
	}
	
	_delay_ms(50);
	
	do
	{
		send_array[0] = pgm_read_byte(&CONFIG2[index]);
		index++;
		send_array[1] = pgm_read_byte(&CONFIG2[index]);
		index++;
		timeout = 0;
		do{
			status = TWI_Master_Transmit(&TWI1, 0x43,2, send_array);
			timeout++;
		}while((status != SUCCESS) && (timeout < 50));
	}while((send_array[0] != 0xFF) && (timeout < 50));

	if(timeout< 50)
	{
		sprintf(prnt_bffr,"Config 2 sent...\n\r");
		UART_Transmit_String(&UART1, 0, prnt_bffr);
	}
	
	index = 0;
	
	do
	{
		send_array[0] = pgm_read_byte(&CONFIG3[index]);
		index++;
		send_array[1] = pgm_read_byte(&CONFIG3[index]);
		index++;
		timeout = 0;
		do{
			status = TWI_Master_Transmit(&TWI1, 0x43,2, send_array);
			timeout++;
		}while((status != SUCCESS) && (timeout < 50));
	}while((send_array[0] != 0xFF) && (timeout < 50));

	if(timeout< 50)
	{
		sprintf(prnt_bffr,"User Config sent...\n\r");
		UART_Transmit_String(&UART1, 0, prnt_bffr);
	}


	// Clear DATA_REQ no more data from STA013
	Output_Clear(&PC, PIN_C6);
	
	if(timeout >= 50)
	{
		return 0;
	}
	else 
	{
		return 0xFF;
	}
}

