/*
 * Read_Inputs.h
 *
 * Created: 11/17/2020 11:17:45 AM
 *  Author: youngerr
 */ 


#ifndef READ_INPUTS_H_
#define READ_INPUTS_H_

#include "board.h"

void Input_Init(uint8_t volatile * port_addr, uint8_t pin_mask);

void Pull_Up_Enable(uint8_t volatile *port_addr, uint8_t pin_mask);

void Pull_Up_Disable(uint8_t volatile *port_addr, uint8_t pin_mask);

uint8_t Read_Inputs(uint8_t volatile * port_addr);

uint8_t Read_Pin(uint8_t volatile * port_addr, uint8_t pin_mask);

#endif /* READ_INPUTS_H_ */