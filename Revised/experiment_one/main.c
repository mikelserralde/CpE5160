/*
 * experiment_one.c
 * Authors : Mikel Serralde & Hayden B. Long
 */ 

#include "board.h"
#include "UART.h"
#include "UART_Print.h"
#include "print_memory.h"
#include "Output_Drivers.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

//const int8_t test[15] PROGMEM = "This is test\n\r";

int main(void)
{
	//Part 3 Output initialization
	Output_Set(&PC , (1<<PORT_USERLED));
	Output_Init(&PC , (1<<DDR_USERLED));

	//Part 6, UART initialization, baud rate = 9600
	UART_Init(&UART1,9600);
	uint8_t testChar = 'U';


	//Part 8 and 9, initialize print buffer, put a string in, and transmit it
	uint8_t testing[7] PROGMEM = "memeing";
	uint8_t * string_p = Export_print_buffer();
	Copy_String_to_Buffer(&testing, 7, &string_p);
	UART_Transmit_String(&UART1, 7, &testing);

	//Part 10, 30+ char string to be printed from memory
	uint8_t message[40] = "Mikel and Hayden, Best Friends Forever";
	print_memory(&UART1, 39, &message);
	
    while (1) 
    {
		
		//Part 3, toggle USER LED
		Output_Clear(&PC, (1<<PORT_USERLED));
		_delay_ms(500);
		Output_Set(&PC, (1<<PORT_USERLED));
		_delay_ms(500);
		
		
		//Part 6, UART transmit ascii U
		UART_Transmit(&UART1, testChar);

		//Part 7, Echo received char into testChar for transmitting
		testChar = UART_Receive(&UART1);
		
		
    }
}

