/*
SPI.c
Holds the function definitions for the SPI initialization and transfers
Created by Hayden Long 10/20/2020
*/

#include <stdio.h>
#include "board.h"
#include "SPI.h"
#include "Control_Outputs.h"
#include "UART.h"
#include "UART_Print.h"



uint8_t SPI_Master_Init(uint8_t volatile* SPI_addr, uint32_t clock_freq)
{
	uint8_t divider = (F_CPU / F_DIV) / clock_freq;

	//Used to return an error if desired max clock value is too low to ACHEIVE
	uint8_t return_value = 0;
	uint8_t clock_rate_error = 1;
	int8_t SD_init_string[22] = "HAYDEN's COde sux :(\n";


	//Set the SPI Clock rate according to divider table
	if (divider < 2)
	{
		*(SPI_addr + SPSR) = 1;
		*(SPI_addr + SPCR) = ((1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2)|0);
	}
	else if (divider < 4)
	{
		*(SPI_addr + SPSR) = 0;
		*(SPI_addr + SPCR) = ((1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2)|0);
	}
	else if (divider < 8)
	{
		//*(SPI_addr + SPCR) = (1<<SPR00);
		*(SPI_addr + SPSR) = 1;
		*(SPI_addr + SPCR) = ((1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2)|0);
	}
	else if (divider < 16)
	{
		//*(SPI_addr + SPCR) = (1 << SPR00);
		*(SPI_addr + SPSR) = 0;
		*(SPI_addr + SPCR) =  ((1 << SPR00) |(1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2)|0);
	}
	else if (divider < 32)
	{
		//*(SPI_addr + SPCR) = (1 << SPR01);
		*(SPI_addr + SPSR) = 1;
		*(SPI_addr + SPCR) =  ((1 << SPR01) |(1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2)|0);
	}
	else if (divider < 64)
	{
		//*(SPI_addr + SPCR) = ((1 << SPR00) | (1<<SPR01));
		*(SPI_addr + SPSR) = 1;
		*(SPI_addr + SPCR) =  ((1 << SPR00) | (1 << SPR01) |(1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2)|0);
	UART_Transmit_String(&UART1, 22, SD_init_string);

	}
	else if (divider < 128)
	{
		//*(SPI_addr + SPCR) = ((1 << SPR00) | (1 << SPR01));
		*(SPI_addr + SPSR) = 0;
		*(SPI_addr + SPCR) =  ((1 << SPR00) | (1 << SPR01) |(1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2)|0);
	}
	else
	{
		return_value = clock_rate_error;
	}

	//Can you do |= with a pointer?
	//Initialize SPCR for a master device, enable SPI, set clock polarity and phase
	//*(SPI_addr + SPCR) |= ((1 << SPE) | (1 << MSTR) | (CPOL_VAL << 3) | (CPHA_VAL << 2));

	//Initialize Clock value according to CPOL_VAL
	if (CPOL_VAL == 0)
	{
		Output_Clear(&PB, SCK);
		Output_Init(&PB, SCK);
	}
	else
	{
		Output_Set(&PB, SCK);
		Output_Init(&PB, SCK);
	}

	//Set MOSI pin as output and initialize at 1
	Output_Set(&PB, MOSI);
	Output_Init(&PB, MOSI);

	return return_value;
}



uint8_t SPI_Transfer(uint8_t volatile * SPI_addr, uint8_t data)
{
	uint8_t status;

	*(SPI_addr + SPDR) = data;

	do
	{
		status = *(SPI_addr + SPSR);
		UART_Transmit(&UART1,status);
	//} while ((status & (1 << SPIF)) == 0);
	}while((status & 0x80) == 0);

	//No error checking

	return *(SPI_addr + SPDR);
}

