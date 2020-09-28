#include uart.h

#define U2X (0)

void UART_Init(uint8_t volatile *UART_addr, uint16_t baud_rate){
	uint16_t UBRR_value = (uint16_t)(((F_CPU/OSC_DIV)/(8UL*(2-U2X)*baud_rate))-1);
	
	// Set Baud Rate
	*(UART_addr+UBRRH) = UBRR_value/256;
	*(UART_addr+UBRRL) = UBRR_value%256;
	
	*(UART_addr+UCSRA) = (U2X<<1);
	
	*(UART_addr+UCSRC) = Asynchronous|No_Parity|One_Stop_Bit|Eight_Data_Bits;
	
	// RX & TX Enabled, no interrupts, no multi-drop
	*(UART_addr+UCSRB) = (RXEN<<1) | (TXEN<<1);
}

uint8_t UART_Transmit(uint8_t volatile *UART_addr, int8_t send_value){
	uint8_t status;
	do{
		status = *(UART_addr+UCSRA);
	}while ((status & (1<<UDRE)) != (1<<UDRE));
	
	*(UART_addr+UDR) = send_value;
	
	return 0;
}

uint8_t UART_Receive(uint8_t volatile *UART_addr){
	uint8_t status;
	uint8_t received_value;
	do{
		status = *(UART_addr+UCSRA);
	}while ((status & (1<<RXC)) != (1<<RXC));
	
	received_value = *(UART_addr+UDR);
	
	return received_value;
}
