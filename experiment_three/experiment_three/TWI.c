/*
 * TWI.c
 *
 * Created: 11/11/2020 
 *  Author: Hayden Long and Mikel Serralde
 */ 

#include "board.h"
#include <avrio.h>

void TWI_Init(uint8_t volatile* TWI_addr, uint32_t clock_rate)
{
	uint32_t prescale = (((F_CPU / F_DIV) / (uint32_t) * (clock_rate)) - 16UL) / 
		(2UL * 255);

	uint32_t TWI_Baud_Rate;
	
	if (prescale < 1)
	{
		*(TWI_addr + TWSR) = 0;
		prescale = 1;
	}

	else if (prescale < 4)
	{
		*(TWI_addr + TWSR) = 0x01;
		prescale = 4;
	}

	else if (prescale < 16)
	{
		*(TWI_addr + TWSR) = 0x02;
		prescale = 16;
	}

	else if (prescale < 64)
	{
		*(TWI_addr + TWSR) = 0x03;
		prescale = 64;
	}

	else
	{
		//ERROR MESSAGE SET CLOCK FREQ TOO LOW
	}


	TWI_Baud_Rate = (((F_CPU / F_DIV) / (uint32_t) * (clock_rate)) - 16UL) /
		(2UL * prescale);

	if (TWI_Baud_Rate > 255)
	{
		//ERROR MESSAGE RECALCULATE PRESCALE / CLOCK FREQ TOO LOW
	}
	else
	{
		*(TWI_addr + TWBR) = (uint8_t)(TWI_Baud_Rate);
	}

}


uint8_t TWI_Master_Transmit(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array);


uint8_t TWI_Master_Receive(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array);