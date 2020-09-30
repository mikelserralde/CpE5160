/*
 * experiment_one.c
 * Authors : Mikel Serralde & Hayden B. Long
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "board.h"
#include "UART.h"
#include "UART_Print.h"
#include "print_memory.h"

const int8_t test[15] PROGMEM = "This is test\n\r";

int main(void)
{
	//Part 3 Output initialization
	Output_Set(&PORT_C , (1<<PORT_USERLED));
	Output_Init(&PORT_C , (1<<DDR_USERLED));

	//Part 6, UART initialization, baud rate = 9600
	UART_Init(&UART1,9600);
	uint8_t testChar = "U";


	//Part 8, initialize print buffer, put a string in, and transmit it
	uint8_t * string_p = Export_print_buffer();
	Copy_String_to_Buffer(test,string_p);
	UART_Transmit_String(&UART1,0,string_p);

	//Part 10, 30+ char string to be printed from memory
	uint8_t message[30] = "Mikel and Hayden, Best Friends Forever\n";
	print_memory(&UART1, 39, message[]);
	
    while (1) 
    {
		
		//Part 3, toggle USER LED
		Output_Clear(&PORT_C, (1<<PORT_USERLED));
		_delay_ms(500);
		Output_Set(&PORT_C, (1<<PORT_USERLED));
		_delay_ms(500);

		//Part 6, UART transmit ascii U
		UART_Transmit(&UART1, testChar);
		_delay_ms(200);

		//Part 7, Echo received char into testChar for transmitting
		testChar = UART_Receive(&UART1);
		_delay_ms(200);
	
    }
}

