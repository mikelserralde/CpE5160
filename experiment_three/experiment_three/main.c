/*
 * experiment_three.c
 *
 * Created: 11/6/2020 6:00:58 PM
 * Author : Mikel
 */ 

#include <avr/io.h>

#define TWI_CLK_RATE 400000

int main(void)
{
	
		// Initialize RESET Pin
	Output_Init(&PB, PIN_B1);
	// Initialize DATA_REQ Pin
	Output_Init(&PC, PIN_C6);
	// Initialize BIT_EN Pin
	Output_Init(&PD, PIN_D6);
	
	TWI_Init(&TWI1, TWI_CLK_RATE);
	
	STA013_Config(&TWI1);

    /* Replace with your application code */
    while (1) 
    {
		
    }
}

