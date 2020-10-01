#include "UART.h"
#include "board.h"
#include <stdio.h>

#define U2X (0)

// Initializes the UART port passed through at the given baud rate
void UART_Init(uint8_t volatile *UART_addr, uint16_t baud_rate
	// Calculates the Baud Rate
	uint16_t UBRR_value = (uint16_t)(((F_CPU/OSC_DIV)/(8UL*(2-U2X)*baud_rate))-1);
	
	// Set UBBRH and UBBRL to the Baud Rate from calculation above
	*(UART_addr+UBRRH) = UBRR_value/256;
	*(UART_addr+UBRRL) = UBRR_value%256;
	
	// U2X Bit set in UCSRA (No other bits need to be set, they are all 0)
	*(UART_addr+UCSRA) = (U2X<<1);
	
	// UCSRC Register Set: Asynchronous, No Parity, One Stop Bit, and Eight Data Bits
	*(UART_addr+UCSRC) = Asynchronous|No_Parity|One_Stop_Bit|Eight_Data_Bits;
	
	
	// RX & TX Enabled, no interrupts, no multi-drop, Char size 8
	*(UART_addr+UCSRB) = ((1<<RXEN) | (1<<TXEN) | (1<<UCSZ2)); 
	
}

uint8_t UART_Transmit(uint8_t volatile *UART_addr, int8_t send_value){
	uint8_t status;
	
	// Loop until the UDRE bit is set in UCSRA
	do{
		status = *(UART_addr+UCSRA);
	}while ((status & (1<<UDRE)) != (1<<UDRE));
	
	// Places the send value into the UDR register
	*(UART_addr+UDR) = send_value;
	
	return 0;
}

uint8_t UART_Receive(uint8_t volatile *UART_addr){
	uint8_t status;
	uint8_t received_value;
	
	// Loops until the RXC bit is set in UCSRA
	do{
		status = *(UART_addr+UCSRA);
	}while ((status & (1<<RXC)) != (1<<RXC));
	
	// Gets and returns the value in the UDR register (also clears RXC)
	received_value = *(UART_addr+UDR);
	return received_value;
}
