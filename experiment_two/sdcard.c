// sdcard.c pseudo code

#define CMD0 (0)
#define CMD8 (8)
#define CMD41 (41)
#define CMD58 (58)

// Return Values: 
// 0x01: Illegal Command Value
// 0xFF: Success
uint8_t Send_Command(uint8_t command, uint32_t argument)
{
	uint8_t checksum = 0x01;
	uint8_t received_byte;

	if(command > 63)
	{
		return 0x01;
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
	received_byte=SPI_Transfer(SPI_Addr, command);
	
	// for(uint8_t i = 4; i>0; i--)
	// {
		// splits up into MSB to LSB bytes in the most complicated way 
		// uint8_t to_send = (argument & ((15*16^((i*2)-1))+(15*16^((i*2)-2))))>>((i-1)*8);
		// SPI_Transfer(SPI_Addr, to_send);
	// }
	
	for(index=0;index<4;index++){
		send_value=(uint8_t)(argument>>(24-(index*8)));
		received_byte=SPI_Transfer(&SD_PORT,send_value);
	}
	
	received_byte=SPI_Transfer(SPI_Addr, checksum);
	
	return 0xFF;
}

// Return Values: 
// 0x00: R1 Response Error 
// 0x01: Timeout 
// 0xFF: Success
uint8_t Receive_Response (uint8_t number_of_bytes, uint8_t * array_name)
{
	uint8_t received_byte;
	uint8_t timeout = 0;
	do{
		received_byte = SPI_Transfer(SPI_Addr, 0xFF);
		timeout++;
		if(timeout > 100)
		{
			return 0x01;
		}
		// delay_ms(50);
	}while((received_byte & 0x80) != 0x80);
	//}while(((received_byte & 0x80) != 0x80) & (timeout < 100));
	
	if(received_byte != 0x01 | received_byte != 0x00)
	{
		return 0x00;
	}
	
	*(array_name) = received_byte;
	
	if(number_of_bytes > 1)
	{
		for(uint8_t i = 1; i < number_of_bytes; i++)
		{
			*(array_name+i) = SPI_Transfer(SPI_Addr, 0xFF);
		}
	}
	
	SPI_Transfer(SPI_Addr, 0xFF);
	
	return 0xFF;
	
}


uint8_t SD_Card_Init(void)
{
	uint8_t response[8]; 
	
	// Set /CS = 1 and send at least 74 clock cycles on SCK
	
	// Clear /CS (= 0) and send CMD0
	Send_Command(CMD0, 
	// Read R1 Response 
	
	
	// Continue if R1 = 0x01. 
	// Set /CS = 1
	
	// Clear /CS and send CMD8 
	// Read R7 Response
	// Set /CS = 1 after response
	// If R1 is = 0x05 (Illegal Command) then SD card is v1.x typedef (handle this)
	// If R1 is not 0x01 (otherwise), function should exit with error flag
	// Check R7 response for correct voltage range
	// If it doesn't match, designate card as unusable?
	
	// Clear /CS and send CMD58
	// Read R3 response
	// Set /CS = 1
	// R1 should be 0x01 (else return error)
	// Check R3 response for correct voltage (else return unusable)
	
	// Clear /CS and send ACMD41 (send CMD 55 and receive R1, then send CMD41)
	// Receive R1 response 
	// If card is v1.x, ACD41 argument = 0, if v2.0, HCS (bit 30) should be set_new_handler
	// Send command sequence until R1 response returns as 0x00 (active state) (or if error occurs), 
	// or until timeout if it doesn't ever go into active state
	//
}