/*
Output Drivers Source Code
*/

#include "Output_Drivers.h"
#include <stdio.h>
#include "board.h"

//Port_addr will get "Px" which is just a base address, i.e. PA for PORT A

// Initializes the pins passed through as output pins for the port 
// address that is pointed to with port_addr.
void Output_Init(uint8_t volatile * port_addr, uint8_t outputs )
{
	// Sets the pins that were passed through as output pins
	*(port_addr + DDR) = outputs;
};


// Clears the pins that are passed through in the pin mask on the port address
// that is pointed to in port_addr.
void Output_Clear(uint8_t volatile * port_addr, uint8_t pin_mask)
{
	// Ands with the ones complement of pin mask to clear the bits that were
	// passed through.
	*(port_addr + PORT) &= (~pin_mask);
};

// Sets the pins as passed through the pin mask on the given port address.
void Output_Set(uint8_t volatile * port_addr, uint8_t pin_mask)
{
	// ORs with the pin mask to set the bits that were passed through
	*(port_addr + PORT) |= (pin_mask);
};

