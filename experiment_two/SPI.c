/*
SPI.c
Holds the function definitions for the SPI initialization and transfers
Created by Hayden Long 10/20/2020
*/

#include <stdio.h>
#include "board.h"
#include "SPI.h"
#include "Control_Outputs.h"



uint8_t SPI_Master_Init(uint8_t volatile* SPI_addr, uint32_t clock_freq)
{
	uint8_t divider = (F_CPU / F_DIV) / clock_freq;

	//Used to return an error if desired max clock value is too low to acheive
	uint8_t return_value = 0;
	uint8_t Clock_rate_error = 1;


	//Set the SPI Clock rate according to divider table
	if (divider < 2)
	{
		*(SPI_addr + SPSR) = 1;
	}
	else if (divider < 4)
	{
		*(SPI_addr + SPSR) = 0;
	}
	else if (divider < 8)
	{
		*(SPI_addr + SPCR) = (1<<SPR00);
		*(SPI_addr + SPSR) = 1;
	}
	else if (divider < 16)
	{
		*(SPI_addr + SPCR) = (1 << SPR00);
		*(SPI_addr + SPSR) = 0;
	}
	else if (divider < 32)
	{
		*(SPI_addr + SPCR) = (1 << SPR01);
		*(SPI_addr + SPSR) = 1;
	}
	else if (divider < 64)
	{
		*(SPI_addr + SPCR) = ((1 << SPR00) | (1<<SPR01));
		*(SPI_addr + SPSR) = 1;
	}
	else if (divider < 128)
	{
		*(SPI_addr + SPCR) = ((1 << SPR00) | (1 << SPR01));
		*(SPI_addr + SPSR) = 0;
	}
	else
	{
		return_value = clock_rate_error;
	}

	//Can you do |= with a pointer?
	//Initialize SPCR for a master device, enable SPI, set clock polarity and phase
	*(SPI_addr + SPCR) |= ((1 << SPE) | (1 << MSTR) | (CPOL << 3) | (CPHA << 2));

	//Initialize Clock value according to CPOL
	if (CPOL == 0)
	{
		Output_Clear(&PB, (1 << SCK));
		Output_Init(&PB, (1 << SCK));
	}
	else
	{
		Output_Set(&PB, (1 << SCK));
		Output_Init(&PB, (1 << SCK));
	}


	return return_value;
}



uint8_t SPI_Transfer(uint8_t* SPI_addr, uint8_t data)
{
	uint8_t status;

	*(SPI_addr + SPDR) = data;

	do
	{
		status = *(SPI_addr + SPSR);
	} while ((status& (1 << SPIF)) == 0);


	//Fuck error checking

	return *(SPI_addr + SPDR);
}

