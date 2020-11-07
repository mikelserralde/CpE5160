#include "STA013.h"
#include <avr/pgmspace.h> 

// Import the labels 
extern const uint8_t CONFIG;
extern const uint8_t CONFIG2;

void STA013_Config() //??? Definitely not what the function is supposed to be
{
	index = 0;

	do
	{
		register_address = pgm_read_byte(&CONGIG[index]);
		index++;
		send_array[0] = pgm_read_byte(&CONFIG[index]);
		index++;
		timeout = 50;
		do{
			status = TWI_Master_Transmit(&TWI1, 0x43, register_address, 1, 1, send_array);
			timeout--;
		}while((status != SUCCESS) && (timeout != 0));
	}while((send_array[0] != 0xFF) && (timeout!=0));
		//if(timeout != 0)
}

