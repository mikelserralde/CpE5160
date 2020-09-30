/*
Output Drivers Source Code
*/

//Port_addr will get "Portx" which is just a base address, 
//PIN offset = 0, DDR offset = 1, and PORT offset = 2


void Output_Init(uint8_t volatile *port_addr, uint8_t outputs )
{
	*(port_addr + 1) = outputs;
};


void Output_Clear(uint8_t volatile* port_addr, uint8_t pin_mask)
{

	*(port_addr + 2) |= (pin_mask);
};


void Ouput_Set(uint8_t volatile* port_addr, uint8_t pin_mask)
{
	*(port_addr + 2) &= (pin_mask);
};

