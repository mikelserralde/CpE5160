// sdcard.c
// by mikel

#include "sdcard.h"
#include "board.h"
#include "Control_Outputs.h"
#include <stdio.h>


uint8_t Send_Command(uint8_t command, uint32_t argument)
{
	uint8_t checksum = 0x01;
	uint8_t received_byte;

	if(command > 63)
	{
		return ILLEGAL_COMMAND;
	}
	
	if(command == CMD8)
	{
		checksum = 0x87;
	}
	else if (command == CMD0)
	{
		checksum = 0x95;
	}
	

	// Sends Command (with transmission bits)
	command |= 0x40;
	received_byte=SPI_Transfer(&SPI0, command);
	
	for(index=0;index<4;index++){
		send_value=(uint8_t)(argument>>(24-(index*8)));
		received_byte=SPI_Transfer(&SD_PORT,send_value);
	}
	
	// Sends Checksum and Stop Bit (1)
	received_byte=SPI_Transfer(&SPI0, checksum);
	
	return SUCCESS;
}


uint8_t Receive_Response(uint8_t number_of_bytes, uint8_t * array_name)
{
	uint8_t received_byte;
	uint8_t timeout = 0;
	do{
		received_byte = SPI_Transfer(&SPI0, 0xFF);
		timeout++;
		if(timeout > 100)
		{
			return TIMEOUT;
		}
		// delay_ms(50);
	}while((received_byte & 0x80) != 0x80);
	
	if(received_byte != 0x01 | received_byte != 0x00)
	{
		return received_byte;
	}
	
	*(array_name) = received_byte;
	
	if(number_of_bytes > 1)
	{
		for(uint8_t i = 1; i < number_of_bytes; i++)
		{
			*(array_name+i) = SPI_Transfer(&SPI0, 0xFF);
		}
	}
	
	SPI_Transfer(&SPI0, 0xFF);
	
	return SUCCESS;
}


// Return Values: 
uint8_t SD_Card_Init(void)
{
	uint8_t response[8]; 
	uint8_t received_value;
	uint8_t timeout = 0;
	
	// Set /CS = 1
	Output_Init(&PB, (1<<SD_CS));
	
	// Send at least 74 clock cycles on SCK
	for(uint8_t i = 0; i<10; i++)
	{
		SPI_Transfer(&SPI0, 0xff);
	}
	
	// Clear /CS (= 0) 
	Output_Clear(&PB, (1<<CS));
	
	// Send CMD0
	received_value = Send_Command(CMD0, 0UL);
	
	if(received_value != 0xFF)
	{
		return received_value;
	}
	// Read R1 Response 
	received_value = Receive_Response(1, &response);
	
	if(received_value != 0xFF)
	{
		return received_value;
	}
	
	// Continue if R1 = 0x01. 
	if(response[0] != 0x01)
	{
		return UNEXPECTED_ACTIVE_STATE;
	}
	
	// Set /CS = 1
	Output_Set(&PB, (1<<CS));
	// Clear /CS and send CMD8 
	Output_Clear(&PB, (1<<CS));
	received_value = Send_Command(CMD8, 0x000001AA);
	
	if(received_value != 0xFF)
	{
		return received_value;
	}
	
	// Read R7 Response
	received_value = Receive_Response(5 , &response);
	
	// Set /CS = 1 after response
	Output_Set(&PB, (1<<CS));
	
	// If R1 is = 0x05 (Illegal Command) then SD card is v1.x typedef (handle this)
	if(received_value != 0xFF)
	{
		return received_value;
	}
	
	// If R1 is not 0x01 (otherwise), function should exit with error flag
	if(response[0] != 0x01)
	{
		return UNEXPECTED_ACTIVE_STATE;
	}
	
	// Check R7 response for correct voltage range
	
	if(response[3] != 0x01)
	{
		return VOLTAGE_ERROR;
	}
	
		
	// Clear /CS 
	Output_Clear(&PB, (1<<CS));
	// Send CMD58
	received_value = Send_Command(CMD58, 0UL);
	if(received_value != 0xFF)
	{
		return received_value;
	}
	
	// Read R3 response
	received_value = Receive_Response(5, &response);
	
	if(received_value != 0xFF)
	{
		return received_value;
	}
	
	// R1 should be 0x01 (else return error)
	if(response[0] != 0x01)
	{
		// Unexpected Active State Error
		return 0x01;
	}
	
	// Check R3 response for correct voltage (else return unusable)
	if((response[2] & 0x30) != 0x30)
	{
		return VOLTAGE_ERROR;
	}
	
	// Set /CS = 1
	Output_Set(&PB, (1<<CS));
	// Clear /CS
	Output_Clear(&PB, (1<<CS));
	// Send ACMD41: Send CMD 55 and receive R1, then send ACMD41
	// Send command sequence until R1 response returns as 0x00 (active state) (or if error occurs), 
	// or until timeout if it doesn't ever go into active state
	do
	{
		Send_Command(CMD55, 0UL);
		if(received_value != 0xFF)
		{
			return received_value;
		}

		// Receive R1 response 
		received_value = Receive_Response(1, &response);

		if(received_value != 0xFF)
		{
			return received_value;
		}

		// If card is v1.x, ACMD41 argument = 0, if v2.0, HCS (bit 30) should be set_new_handler
		received_value = Send_Command(ACMD41, 0x40000000);
		if(received_value != 0xFF)
		{
			return received_value;
		}

		// Receive R1 response 
		received_value = Receive_Response(1, &response);

		if(received_value != 0xFF)
		{
			return received_value;
		}
		
		timeout++;
		if(timeout > 100)
		{
			return 0x01;
		}
	}while(received_value != 0x00);
	
	
	// Send CMD58
	received_value = Send_Command(CMD58, 0UL);
	if(received_value != 0xFF)
	{
		return received_value;
	}
	
	// Read R3 response
	received_value = Receive_Response(5, &response);
	
	if(received_value != 0xFF)
	{
		return received_value;
	}
	
	// R1 should be 0x00 (else return error)
	if(response[0] != 0x00)
	{
		// Unexpected Idle State Error
		return UNEXPECTED_IDLE_STATE;
	}
	
	// Check R3 response OCR and CCS bits
	if((response[1] & 0xC0) != 0xC0)
	{
		return CARD_CAPACITY_ERROR;
	}
	
	Output_Set(&PB, (1<<CS));
	return SUCCESS;
}

uint8_t Read_Block(uint16_t number_of_bytes, uint8_t * array)
{
	uint8_t received_byte;
	uint8_t timeout = 0;

	// Clear /CS
	Output_Clear(&PB, (1<<CS));

	// Loop until receive R1 response
	do{
		received_byte = SPI_Transfer(&SPI0, 0xFF);
		timeout++;
		if(timeout > 100)
		{
			return TIMEOUT;
		}
		// delay_ms(50);
	}while((received_byte & 0x80) != 0x80);
	
	if(received_byte != 0x00)
	{
		return INACTIVE_CARD;
	}

	// Loop until get something other than 0xFF
	timeout = 0;
	do{
		received_byte = SPI_Transfer(&SPI0,0xFF);
		if(timeout > 100)
		{
			return TIMEOUT;
		}
	}while(received_byte==0xFF);
	
	// Check for data start token
	if(received_byte != 0xFE)
	{
		return received_byte;
	}
	
	// Read all bytes of data block
	for(uint8_t i = 0; i<number_of_bytes; i++)
	{
		received_byte = SPI_Transfer(&SPI0,0xFF);
		*(array+i) = received_byte;
	}
	
	// Receive CRC16 (do nothing with it) and send a final 0xFF
	for(uint8_t i = 0; i<3; i++)
	{
		received_byte = SPI_Transfer(&SPI0,0xFF);
	}

	// Set /CS = 1
	Output_Set(&PB, (1<<CS));
	
	return SUCCESS;
}