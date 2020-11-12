#include "STA013.h"
#include <avr/pgmspace.h> 

// Import the labels 
extern const uint8_t CONFIG;
extern const uint8_t CONFIG2;

void STA013_Config() //??? Definitely not what the function is supposed to be
{
	// Read 0xAC from ID register
	uint8_t timeout = 0;
	uint8_t index = 0;
	uint8_t status;
	uint8_t receive_array[50];
	uint8_t send_array[2];
	
	do
	{
		status = TWI_Master Recieve(&TWI1, 0x43, 4, receive_array);
		timeout++;
	}while((timeout<50) && (status != SUCCESS));
	
	
	do
	{
		send_array[0] = pgm_read_byte(&CONGIG[index]);
		index++;
		send_array[1] = pgm_read_byte(&CONFIG[index]);
		index++;
		timeout = 0;
		do{
			status = TWI_Master_Transmit(&TWI1, 0x43,2, send_array);
			timeout++;
		}while((status != SUCCESS) && (timeout < 50));
	}while((send_array[0] != 0xFF) && (timeout < 50));
		//if(timeout != 0)
}

