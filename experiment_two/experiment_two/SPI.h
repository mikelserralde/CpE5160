/*
SPI.h 
Holds the function prototypes for the SPI initialization and transfers
Created by Hayden Long 10/20/2020
*/

#ifndef SPI_H_
#define SPI_H_


#include <stdint.h>
#include "board.h"


#define SPR00 0
#define SPR01 1
#define MSTR 4
#define DORD 5
#define SPE 6
#define SPIE 7

#define SPI2 0
#define SPIF 7
#define WCOL 6

#define CPOL_VAL 0
#define CPHA_VAL 0



/*
Description: Enables SPI transfers as Master device, sets clock phase and polarity,
	and determines the clock frequency
INPUTS: SPI base address, desired maximum clock frequency
OUTPUTS: returns error if desired maximum clock frequency is too low
*/

uint8_t SPI_Master_Init(uint8_t volatile* SPI_addr, uint32_t clock_freq);


/*
Description: Transfers data between master and slave devices
INPUTS: SPI base address, data byte to be transfered
OUTPUTS: returns the byte value received from slave
*/


uint8_t SPI_Transfer(uint8_t volatile * SPI_addr, uint8_t data);


#endif //SPI_H_