/*
Output Driver Header File
*/

#ifndef OUTPUT_DRIVERS_H
#define OUTPUT_DRIVERS_H

#include "board.h"
#include <stdio.h>


//The DDR register is set equal to "outputs"

void Output_Init(uint8_t volatile * port_addr, uint8_t outputs);

//Pin_mask is ORed with the port register to set bits with 1
//and leave those with 0 alone.

void Output_Clear(uint8_t volatile * port_addr, uint8_t pin_mask);


//Pin_mask is ANDed with the port register to clear bits with 0
//and leave those with 1 alone.

void Output_Set(uint8_t volatile * port_addr, uint8_t pin_mask);



#endif //OUTPUT_DRIVERS_H