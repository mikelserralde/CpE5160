/*
Output Drivers Source Code
*/

#include "Output_Drivers.h"
#include <stdio.h>
#include "board.h"

//Port_addr will get "Portx" which is just a base address, 


void Output_Init(uint8_t volatile * port_addr, uint8_t outputs )
{
	*(port_addr + DDR) = outputs;
};


void Output_Clear(uint8_t volatile * port_addr, uint8_t pin_mask)
{
	
	*(port_addr + PORT) &= (~pin_mask);
};


void Output_Set(uint8_t volatile * port_addr, uint8_t pin_mask)
{
	
	*(port_addr + PORT) |= (pin_mask);
};

