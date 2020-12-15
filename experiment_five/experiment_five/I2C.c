#include <avr/io.h>
#include "board.h"
#include "I2C.h"
#include <stdio.h>




/***********************************************************************
DESC:    Sets the Prescale and Clock Rate Generator for the two wire interface
INPUT: Desired SCL clock frequency
RETURNS: Nothing
CAUTION: 
          
************************************************************************/

uint8_t TWI_Master_Init(uint8_t volatile *TWI_addr, uint32_t I2C_FREQ)
{
	uint32_t temp32;
	uint8_t Prescale=0, return_val=0;
	
	temp32 = ((F_CPU/F_DIV)/I2C_FREQ)-16;
	while(temp32>256)
	{
		temp32=temp32/4;
		Prescale++;
	}
	if(Prescale>3)
	{
		return_val=0x8A;
	}
	else
	{
		*(TWI_addr+TWSR)=Prescale;
		*(TWI_addr+TWBR)=(uint8_t)temp32;
	}
	return return_val;
	
}



/***********************************************************************
DESC:    Creates the signals required for transmitting bytes using
         the I2C bus.
RETURNS: Error Flag
CAUTION: 
          
************************************************************************/

uint8_t TWI_Master_Transmit(uint8_t volatile *TWI_addr, uint8_t device_addr, uint32_t internal_addr, uint8_t int_addr_bytes, uint8_t num_bytes, uint8_t *send_array)
{
  uint8_t send_val, return_val, index, status;
  volatile uint8_t temp8; 
  return_val=no_errors;
  send_val=device_addr<<1; // lsb is 0 for W
  index=0;
  // Send START 
  *(TWI_addr+TWCR) = 0xA4;   // TWIINT=1 to clear flag, TWSTA=1 for Start, TWEN=1
  do 
  {
	 status=*(TWI_addr+TWCR);
  } while ((status&0x80)==0);
  temp8=(*(TWI_addr+TWSR)&0xF8);
  if(temp8==0x08)   // Start sent
  {
	  *(TWI_addr+TWDR)=send_val;
	  *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1  
  }
  else
  {
	  return_val=bus_busy_error;
  }
  /**** Send Internal Address *****/
  if((int_addr_bytes!=0)&&(return_val==no_errors))
  {
	  index=4-int_addr_bytes;
	  while((index<4)&&(return_val==no_errors))
	  {
		   send_val=(uint8_t)(internal_addr>>(8*(3-index)));
		   index++;
		   do
		   {
			   status=*(TWI_addr+TWCR);
		   } while ((status&0x80)==0);
		   temp8=(*(TWI_addr+TWSR)&0xF8);
		   if(temp8==0x18)   // SLA+W sent, ACK received
		   {
			   *(TWI_addr+TWDR)=send_val;
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			   
		   }
		   else if(temp8==0x28)  // Data sent, ACK received
		   {
			   *(TWI_addr+TWDR)=send_val;
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			   
		   }
		   else if(temp8==0x20)  // SLA+W sent, NACK received
		   {
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0);
			   return_val=NACK_error;
		   }
		   else if(temp8==0x30)  // Data sent, NACK received
		   {
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared
			   return_val=NACK_error;
		   }
		   else if(temp8==0x38)  // Arbitration lost
		   {
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			   return_val=bus_busy_error;
		   }
	  }
  }
  index=0;	  
  /**** Send Data Bytes ******/
  if(return_val==no_errors)
  {
	   while((num_bytes!=0)&&(return_val==no_errors))
	   {
		   send_val=send_array[index];
		   index++;
		   num_bytes--;
		   do
		   {
			   status=*(TWI_addr+TWCR);
		   } while ((status&0x80)==0);    // Wait for TWINT to be set
		   temp8=(*(TWI_addr+TWSR)&0xF8);
		   if(temp8==0x18)   // SLA+W sent, ACK received
		   {
			   *(TWI_addr+TWDR)=send_val;
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			   
		   }
		   else if(temp8==0x28)  // Data sent, ACK received
		   {
			   *(TWI_addr+TWDR)=send_val;
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			   
		   }
		   else if(temp8==0x20)  // SLA+W sent, NACK received
		   {
			   *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared
			   return_val=NACK_error;
		   }
		   else if(temp8==0x30)  // Data sent, NACK received
		   {
			   *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared
			   return_val=NACK_error;
		   }
		   else if(temp8==0x38)  // Arbitration lost
		   {
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			   return_val=bus_busy_error;
		   }
	   }
	   if(return_val==no_errors)
	   {
		   do
		   {
			   status=*(TWI_addr+TWCR);
		   } while ((status&0x80)==0);    // Wait for TWINT to be set
		   temp8=(*(TWI_addr+TWSR)&0xF8);
		   if(temp8==0x18)   // SLA+W sent, ACK received
		   {
			   *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
		   }
		   else if(temp8==0x28)  // Data sent, ACK received
		   {
			   *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
		   }
		   else if(temp8==0x20)  // SLA+W sent, NACK received
		   {
			   *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
			   return_val=NACK_error;
		   }
		   else if(temp8==0x30)  // Data sent, NACK received
		   {
			   *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
			   do
			   {
				   status=*(TWI_addr+TWCR);
			   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
			   return_val=NACK_error;
		   }
		   else if(temp8==0x38)  // Arbitration lost
		   {
			   *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			   return_val=bus_busy_error;
		   }
	   }
  }
	   
  return return_val;
}

/***********************************************************************
DESC:    Creates the signals required for receiving bytes using
         the I2C bus.
RETURNS: Error Flag
CAUTION: 
          
************************************************************************/


uint8_t TWI_Master_Receive(uint8_t volatile *TWI_addr, uint8_t device_addr, uint32_t internal_addr, uint8_t int_addr_bytes, uint8_t num_bytes, uint8_t * rec_array)
{
  uint8_t temp8, send_val, return_val, index, status;
  
  return_val=no_errors;
  if(int_addr_bytes!=0)
  {
	  return_val=TWI_Master_Transmit(TWI_addr,device_addr,internal_addr, int_addr_bytes,0,&send_val);
  }
  send_val=((device_addr<<1)|0x01); // lsb is 1 for R
  index=0;
  // Send START
  *(TWI_addr+TWCR) = 0xA4;   // TWIINT=1 to clear flag, TWSTA=1 for Start, TWEN=1
  do
  {
	  status=*(TWI_addr+TWCR);
  } while ((status&0x80)==0); // Wait for Status flag to be set
  temp8=(*(TWI_addr+TWSR)&0xF8);
  if((temp8==0x08)||(temp8==0x10))   // Start or Repeated Start sent
  {
	  *(TWI_addr+TWDR)=send_val;
	  *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
  }
  else
  {
	  return_val=bus_busy_error;
  }
  if(return_val==no_errors)
  {
	  do
	  {
		  status=*(TWI_addr+TWCR);
	  } while ((status&0x80)==0); // Wait for Status flag to be set
	  temp8=(*(TWI_addr+TWSR)&0xF8);
	  if(temp8==0x40)   // SLA+R sent, ACK received
	  {
		  if(num_bytes==1)
		  {
			 *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEA=0 for NACK, TWEN=1 
		  }
		  else
		  {
			  *(TWI_addr+TWCR) = 0xC4;   // TWIINT=1 to clear flag, TWEA=1 for ACK, TWEN=1
		  }
	  }
	  else if(temp8==0x48)  // SLA+R sent, NACK received
	  {
		  *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
		  do
		  {
			  status=*(TWI_addr+TWCR);
		  } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
		  return_val=NACK_error;
	  }
	  else
	  {
		  return_val=bus_busy_error;
	  }
  }
  index=0;
  if(return_val==no_errors)
  {
	  while((num_bytes!=0)&&(return_val==no_errors))
	  {
		  do
		  {
			  status=*(TWI_addr+TWCR);
		  } while ((status&0x80)==0); // Wait for Status flag to be set
		  temp8=(*(TWI_addr+TWSR)&0xF8);
		  if(temp8==0x50)   // Data byte received, ACK sent
		  {
			num_bytes--;
			rec_array[index]=*(TWI_addr+TWDR);
			index++;
			if(num_bytes==1)
			{
				*(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEA=0 for NACK, TWEN=1
			}
			else
			{
				*(TWI_addr+TWCR) = 0xC4;   // TWIINT=1 to clear flag, TWEA=1 for ACK, TWEN=1
			}
		  }
		  else if(temp8==0x58)  // Data byte received, NACK sent
		  {
			  num_bytes--;
			  rec_array[index]=*(TWI_addr+TWDR);
			  index++;
			  *(TWI_addr+TWCR) = 0x94;   // TWIINT=1 to clear flag, TWSTO=0 for Stop, TWEN=1
			  do
			  {
				  status=*(TWI_addr+TWCR);
			  } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
		  }
		  else if(temp8==0x38)  // Arbitration lost
		  {
			  *(TWI_addr+TWCR) = 0x84;   // TWIINT=1 to clear flag, TWEN=1
			  return_val=bus_busy_error;
		  }
	  }
  }
  return return_val;
}




