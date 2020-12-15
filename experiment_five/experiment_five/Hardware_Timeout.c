/*
 * Hardware_Timeout.c
 *
 * Created: 11/21/2020 9:18:19 PM
 *  Author: ryoun
 */ 
#include <avr/io.h>
#include "board.h"

uint8_t Hardware_Timeout_Start(uint8_t volatile *TC_addr, uint16_t interval_ms)
{
   uint16_t reload,prescale;
   uint8_t return_value,prescale_value,TIFR_offset;
   return_value=0;
   prescale=(uint16_t)(((F_CPU/(100*F_DIV))*(interval_ms))/(655360UL));
   if(prescale<1)
   {
	   prescale_value=1;
	   prescale=1;
   }
   else if(prescale<8)
   {
	   prescale_value=2;
	   prescale=8;
   }
   else if(prescale<64)
   {
	   prescale_value=3;
	   prescale=64;
   }
   else if(prescale<256)
   {
	   prescale_value=4;
	   prescale=256;
   }
   else if(prescale<1024)
   {
	   prescale_value=5;
	   prescale=1024;
   }
   else
   {
	   prescale_value=0;
	   prescale=1024;
	   return_value=0x8F;
   }
   reload=(uint16_t)(((F_CPU/(100*F_DIV))*(interval_ms))/(prescale*10UL));
   /* Determine the address for the TIFR register */
   if(TC_addr==&TC1)
   {
	   TIFR_offset=TIFR1_offset;
   }
   else if(TC_addr==&TC3)
   {
	   TIFR_offset=TIFR3_offset;
   }
   else
   {
	   TIFR_offset=TIFR4_offset;
   }
   *(&TIFR_base+TIFR_offset)=(1<<OCRA_bit);  // Clear the OCRA flag
   *(TC_addr + TCCRA)=0;   // No output control, WGM[1:0]=‘00’ (0=Mode 4)
   *(TC_addr + TCCRC)=0;   // No output forcing
   *(TC_addr + OCRAH)=(uint8_t)(reload>>8);
   *(TC_addr + OCRAL)=(uint8_t)(reload&0xFF);
   *(TC_addr + TCNTH)=0;
   *(TC_addr + TCNTL)=0;   // Set starting timer value to 0x0000
   *(TC_addr + TCCRB)=((1<<3)|prescale_value);  //WGM[3:2] bits 3 and 4, (1=Mode 4)
   return return_value;
}

uint8_t Hardware_Timeout_Check(uint8_t volatile *TC_addr)
{
   uint8_t TIFR_offset,TI_status,return_value;
   /* Determine the address for the TIFR register */
   if(TC_addr==&TC1) 
   {
      TIFR_offset=TIFR1_offset;
   }
   else if(TC_addr==&TC3) 
   {
      TIFR_offset=TIFR3_offset;
   }
   else 
   {
      TIFR_offset=TIFR4_offset;
   }
   TI_status=*((&TIFR_base)+TIFR_offset);
   if((TI_status&(1<<OCRA_bit))!=0)
   {
	   return_value=1;
	   *(TC_addr + TCCRB)=0;   // stops the timer when the timeout is set
   }
   else
   {
	   return_value=0;
   }
   return return_value;
   
}


void Hardware_Timeout(uint8_t volatile *TC_addr, uint16_t delay_ms)
{
	uint16_t reload,index;
	uint8_t return_value,prescale_value,TIFR_offset,TI_status;
	return_value=0;
	  
	/* Determine the address for the TIFR register */
	if(TC_addr==&TC1)
	{
		TIFR_offset=TIFR1_offset;
	}
	else if(TC_addr==&TC3)
	{
		TIFR_offset=TIFR3_offset;
	}
	else
	{
		TIFR_offset=TIFR4_offset;
	}
	*(&TIFR_base+TIFR_offset)=(1<<OCRA_bit);  // Clear the OCRA flag
	*(TC_addr + TCCRA)=0;   // No output control, WGM[1:0]=‘00’ (0=Mode 4)
	*(TC_addr + TCCRC)=0;   // No output forcing
	*(TC_addr + OCRAH)=62;
	*(TC_addr + OCRAL)=128;
	*(TC_addr + TCNTH)=0;
	*(TC_addr + TCNTL)=0;   // Set starting timer value to 0x0000
	*(TC_addr + TCCRB)=((1<<3)|1);  //WGM[3:2] bits 3 and 4, (1=Mode 4)
    //Loop repeatedly for the specified number of milliseconds
    for(index=0;index<delay_ms;index++)
    {
	   do
	   {
		    TI_status=*((&TIFR_base)+TIFR_offset);
	   } while ((TI_status&(1<<OCRA_bit))==0);
	   *((&TIFR_base)+TIFR_offset)=(1<<OCRA_bit);
    }
    *(TC_addr + TCCRB)=0;
}
