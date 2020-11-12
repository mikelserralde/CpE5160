/*
 * experiment_three.c
 *
 * Created: 11/6/2020 6:00:58 PM
 * Author : Mikel
 */ 

#include <avr/io.h>


int main(void)
{
	
		// Initialize RESET Pin
	Output_Init(&PB, PIN_B1);
	// Initialize DATA_REQ Pin
	Output_Init(&PC, PIN_C6);
	// Initialize BIT_EN Pin
	Output_Init(&PD, PIN_D6);
	

    /* Replace with your application code */
    while (1) 
    {
    }
}

