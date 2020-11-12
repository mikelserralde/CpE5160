#include "STA013.h"
#include <avr/pgmspace.h> 
#include "UART.h"




// Import the labels 
extern const uint8_t CONFIG;
extern const uint8_t CONFIG2;
extern const uint8_t CONFIG3;

void STA013_Config(void) //??? Definitely not what the function is supposed to be
{
	// Read 0xAC from ID register
	uint8_t timeout = 0;
	uint8_t index = 0;
	uint8_t status;
	uint8_t receive_array[3];
	uint8_t send_array[2];
	int8_t prnt_bffr[64];
	
	
	/*
	i=timeout_val; // This value is the number of attempts
	do
	{
	error=TWI_Master_Read(&TWI1,0x43,0,0,3,array_name);
	i--;
	}while((error!=no_errors)&&(i!=0));
	sprintf(prnt_bffr, “Received Value = %2.2bX\n\r”, array_name[2]);
	UART_Transmit_String(&UART1,0,prnt_bffr);
*/
	
	do
	{
		status = TWI_Master Recieve(&TWI1, 0x43, 3, receive_array);
		timeout++;
	}while((timeout<50) && (status != SUCCESS));
	sprintf(prnt_bffr, “Received Value = %2.2bX\n\r”, receive_array[2]);
	UART_Transmit_String(&UART1,0,prnt_bffr);

	
	do
	{
		send_array[0] = pgm_read_byte(&CONFIG[index]);
		index++;
		send_array[1] = pgm_read_byte(&CONFIG[index]);
		index++;
		timeout = 0;
		do{
			status = TWI_Master_Transmit(&TWI1, 0x43,2, send_array);
			timeout++;
		}while((status != SUCCESS) && (timeout < 50));
	}while((send_array[0] != 0xFF) && (timeout < 50));

	if(timeout< 50)
	{
		sprintf(prnt_bffr,“Config 1 sent...”\n\r);
		UART_Transmit_String(&UART1, 0, prnt_bffr);
	}
	
	_delay(50);
	
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
		sprintf(prnt_bffr,“Config 2 sent...”\n\r);
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
		sprintf(prnt_bffr,“User Config sent...”\n\r);
		UART_Transmit_String(&UART1, 0, prnt_bffr);
	}

	
}

