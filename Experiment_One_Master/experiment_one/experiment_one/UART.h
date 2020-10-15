#ifndef UART_H_
#define UART_H_

// ????
#include board.h

// ???
#define Asynchronous (0<<6)
#define Synchronous (1<<6)
#define No_Parity (0<<4)
#define Even_Parity (2<<4)
#define Odd_Parity (3<<4)
#define One_Stop_Bit (0<<3)
#define Two_Stop_Bits (1<<3)
#define Eight_Data_Bits (3)
#define Nine_Data_Bits (7)


// This function initializes the UART port that is passed through 
// with the given baud rate. 
void UART_Init(uint8_t volatile *UART_addr, uint16_t baud_rate);

// This function transmits the given value over the UART port that
// was passed through.
uint8_t UART_Transmit(uint8_t volatile *UART_addr, int8_t send_value);

// This function receives the data from the UART port that was passed 
// through.
uint8_t UART_Receive(uint8_t volatile *UART_addr);

#endif UART_H_