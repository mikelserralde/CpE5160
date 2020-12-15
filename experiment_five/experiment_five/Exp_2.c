///*
 //* Exp_2.c
 //*
 //* Created: 11/14/2014 4:47:16 PM
 //*  Author: youngerr
 //*/ 
//
//#include "Main.h"
//#include "port.h"
//#include "Hardware_delay.h"
//#include "UART.h"
//#include <stdio.h>
//#include "print_bytes.h"
//#include "LCD_Routines.h"
//#include "SPI.h"
//#include "SDCard.h"
//#include "Read_Sector.h"
//#include "Long_Serial_In.h"
//#include "Directory_Functions_struct.h"
//#include "File_System_v2.h"
//#include "I2C.h"
//#include "STA013_config.h"
//
//static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
//
//uint8_t buffer1[512];
//// buffer2[512];
///**
 //* \brief Main routine
 //*/
//int main(void)
//{
	//// Variable to put switch input into
	//uint8_t index, error_flag;
	//uint8_t print_buffer[25];
	//uint16_t temp16, num_entries, entry_num;
	//uint32_t Current_directory, Entry_clus;
	//FS_values_t * Drive_p;
//
	///* Use port D for output to control the STK600 LEDs.
	 //*
	 //* First set the data direction register to 0xff in order to set all
	 //* port pins to output function.
	 //*/
	//DDRLED = 0xfe;  // all outputs except for RxD0
//
	//// Set output levels high. Will turn off STK600 LEDs.
	//PORTLED = 0xff;
//
	//// Set output levels low. Will turn on STK600 LEDs.
	////PORTLED &=~(1 << PORTLED_RED);
    //// Set CPU clock prescaler
	//temp16=OSC_DIV;
	//index=0;
	//while(temp16>1)
	//{
		//index++;
		//temp16=temp16>>1;
	//}
    //CLKPR = 0x80;   // Set CLKPCE bit to enable prescale change
	//CLKPR = index;   // Set prescale value to 1
	///* For input we use port B in order to read input from the STK600
	 //* switches.
	 //*
	 //* We don't need to set these pins to input after reset since they
	 //* are default set as inputs after reset.
	 //*
	 //* But a typical requirement when reading switches are pull-ups. STK600
	 //* don't require these, but we enable the internal pull-ups just to be
	 //* on the safe side.
	 //*/
	//DDRSW = 0;
	//PORTSW = 0xff;
//
	///* Read STK600 switches on port B inputs into a variable.
	 //*
	 //* Press any of the STK600 switches in order to see a difference here.
	 //* A press will be seen as bit value 0 and not press is 1 due to
	 //* pull-ups.
	 //*/
	//
//
//
	///* It's also possible to control a single or a set of pins on a port.
	 //*
	 //* Setting pin PD0 high in order to turn off LED0.
	 //*/
	////PORTLED |= (1 << PORTLED_RED);
//
	//// Setting pin PD1 low in order to turn on LED1.
	////PORTLED &= ~(1 << PORTLED_YELLOW);
    //
	//uart_init();
		//
	//
	//LCD_Port_Init();
	//LCD_Init();
	//sprintf(print_buffer,"Hello LCD");
	//LCD_Print(0,print_buffer);
	//
	//stdout = &mystdout;
	//printf("Print Memory Test\r\n");
	//index=0;
	//
	//error_flag = SPI_Master_Init(400000);
	//if(error_flag==no_errors)
	//{
		//error_flag = SD_card_init();
	//}
	//else
	//{
		//PORTLED &= ~(1 << PORTLED_RED);
		//while(1);
	//}
	//if(error_flag==no_errors)
	//{
		//error_flag = SPI_Master_Init(10000000);
		//PORTLED &= ~(1 << PORTLED_AMBER);
	//}
	//else
	//{
		//PORTLED &= ~(1 << PORTLED_RED);
		//while(1);
	//}
	//// Alternate method of printing
////    while((print_buffer[index])!=0)
////	{
////		uart_putchar(print_buffer[index]);
////		index++;
////	}
    //
    //error_flag = Mount_Drive(buffer1);
	//if(error_flag!=no_errors)
	//{
		//PORTLED &= ~(1 << PORTLED_RED);
		//while(1);
	//}
	//I2C_Master_Init(50000);
	//STA013_init();
	//Drive_p=Export_Drive_values();
	//Current_directory=Drive_p->FirstRootDirSec;
	//for(;;)
	//{
		//printf("Directory Sector = %lu\n\r",Current_directory);
		//num_entries=Print_Directory(Current_directory, buffer1);
		//printf("Enter Selection = ");
		//entry_num=(uint16_t)long_serial_input();
		//if(entry_num<=num_entries)
		//{
			//Entry_clus=Read_Dir_Entry(Current_directory, entry_num, buffer1);
			//if((Entry_clus&directory_bit)==directory_bit)
			//{
				//Entry_clus&=0x0FFFFFFF;
				//Current_directory=First_Sector(Entry_clus);
			//}
			//else
			//{
				//Open_File(Entry_clus, buffer1);
				////Play_Song(Entry_clus);
			//}
			//
		//}
		//else
		//{
			//printf("Invalid Selection\n\r");
		//}
	//}
//}