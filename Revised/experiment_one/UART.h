#ifndef UART_H_
#define UART_H_

#include "board.h"
#include <stdio.h>

// All functions expect a pointer to a UARTn address to be passed 
// through, where n is any of the UART ports, i.e. UART1 or UART2.

// This function initializes the UART port that is passed through 
// with the given baud rate. 
void UART_Init(uint8_t volatile *UART_addr, uint16_t baud_rate);

// This function transmits the given value over the UART port that
// was passed through.
uint8_t UART_Transmit(uint8_t volatile *UART_addr, int8_t send_value);

// This function receives the data from the UART port that was passed 
// through. It returns the received data.
uint8_t UART_Receive(uint8_t volatile *UART_addr);

#endif //UART_H_