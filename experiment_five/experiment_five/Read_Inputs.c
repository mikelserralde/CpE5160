/*
 * Read_Inputs.c
 *
 * Created: 11/17/2020 11:12:47 AM
 *  Author: youngerr
 */ 

#include "board.h"


void Input_Init(uint8_t volatile * port_addr, uint8_t pin_mask)
{
    *(port_addr+DDR)&=(~pin_mask);
}


void Pull_Up_Enable(uint8_t volatile *port_addr, uint8_t pin_mask)
{
	*(port_addr+PORT)|=(pin_mask);    // Set PORTx pin to value of '1'
}

void Pull_Up_Disable(uint8_t volatile *port_addr, uint8_t pin_mask)
{
	*(port_addr+PORT)&=(~(pin_mask));    // Set PORTx pin to value of '1'
}

uint8_t Read_Inputs(uint8_t volatile * port_addr)
{
    return *(port_addr+PIN);  // returns the value in the PIN reg.
}

uint8_t Read_Pin(uint8_t volatile * port_addr, uint8_t pin_mask)
{
	uint8_t temp8;   
	temp8 = *(port_addr+PIN);     
	if((temp8&pin_mask)==0) temp8 = 0; // return ‘0’ if pin==0   
	else temp8 = 1;                    // return ‘1’ if pin==1
    return temp8;
}

