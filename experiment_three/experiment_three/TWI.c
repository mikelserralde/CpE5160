/*
 * TWI.c
 *
 * Created: 11/11/2020 
 *  Author: Hayden Long and Mikel Serralde
 */ 

#include "board.h"
#include "TWI.h"
#include <avr/io.h>

uint8_t TWI_Init(uint8_t volatile* TWI_addr, uint32_t clock_rate)
{
	uint32_t prescale = (((F_CPU / F_DIV) / (uint32_t) * (clock_rate)) - 16UL) / (2UL * 255);

	uint32_t TWI_Baud_Rate;
	
	if (prescale < 1)
	{
		*(TWI_addr + TWSR) = 0;
		prescale = 1;
	}

	else if (prescale < 4)
	{
		*(TWI_addr + TWSR) = 0x01;
		prescale = 4;
	}

	else if (prescale < 16)
	{
		*(TWI_addr + TWSR) = 0x02;
		prescale = 16;
	}

	else if (prescale < 64)
	{
		*(TWI_addr + TWSR) = 0x03;
		prescale = 64;
	}

	else
	{
		return LOW_CLOCK_FREQ;
	}


	TWI_Baud_Rate = (((F_CPU / F_DIV) / (uint32_t) *(clock_rate)) - 16UL) / (2UL * prescale);

	if (TWI_Baud_Rate > 255)
	{
		return RECALC_PRESCALE;
	}
	else
	{
		*(TWI_addr + TWBR) = (uint8_t)(TWI_Baud_Rate);
	}

	return SUCCESS;
}


uint8_t TWI_Master_Transmit(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array)
{

	uint8_t send_value;
	uint8_t status;
	uint8_t temp8;

	//start by sending the slave address + write bit
	send_value = slave_addr << 1;  //lsb for r/w bit, will be 0 for w

	//Start TWI Communication, send command, start signal, enable peripheral
	*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));


	//Wait for TWINT to be set, meaning command has been sent
	do
	{
		status = *(TWI_addr + TWCR);
	} while ((status & 0x80) == 0);

	//Read status code to determine next steps
	temp8 = (*(TWI_addr + TWSR) & 0xF8);

	//Check that start signal was sent then send SLA+W
	if (temp8 == 0x08)
	{
		*(TWI_addr + TWDR) = send_value;
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWEN));
	}
	else
	{
		return temp8;
	}

	//While loop sends data bytes until all bytes are sent or error
	uint16_t index = 0;
	while (num_bytes != 0)
	{
		send_value = array[index];
		index++;
		num_bytes--;

		//wait until TWINT is set, command is done sending
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status & 0x80) == 0);

		//Read status code to determine next steps
		temp8 = (*(TWI_addr + TWSR) & 0xF8);

		//Check if SLA+W was sent and ACK received
		if (temp8 == 0x18)
		{
			*(TWI_addr + TWDR) = send_value;
			*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWEN));
		}
		else if (temp8 == 0x28)  //Check if Data was sent and ACK received 
		{
			*(TWI_addr + TWDR) = send_value;
			*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWEN));
		}
		else if (temp8 == 0x20)  //Check if SLA+W was sent but NACK was received
		{
			//Stop Transfer
			*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
			do
			{
				status = *(TWI_addr + TWCR);
			} while ((status& (1 << TWSTO)) != 0); //Wait for stop = 0
			
			return NACK_ERROR_SLAW;
		}
		else if (temp8 == 0x30)  //Check if Data was sent but NACK was received
		{
			*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
			do
			{
				status = *(TWI_addr + TWCR);
			} while ((status & (1 << TWSTO)) != 0); //Wait for stop = 0

			return NACK_ERROR_DATA;
		}
		else if (temp8 == 0x38)  //Check if arbitration lost in SLA+W or Data bytes
		{
			//Stop transfer here, SDA is low when it should be high
			//Super weird if we get this, since no other masters on line
			*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
			do
			{
				status = *(TWI_addr + TWCR);
			} while ((status & (1 << TWSTO)) != 0); //Wait for stop = 0

			return ARBITRATION_ERROR;
		}

	}

	//All bytes have been sent, send stop condition
	if(temp8 == 0x18)
	{
		//Stop Transfer
		*(TWI_addr + TWDR) = send_value;
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status& (1 << TWSTO)) != 0); //wait for stop=0, stop condition was sent
	}
	else if(temp8 == 0x28)  //Check if Data was sent and ACK received 
	{
		*(TWI_addr + TWDR) = send_value;
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status& (1 << TWSTO)) != 0); //wait for stop=0, stop condition was sent
	}
	else if(temp8 == 0x20)  //Check if SLA+W was sent but NACK was received
	{
		//Stop Transfer
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status & (1 << TWSTO)) != 0); //Wait for stop = 0

		return NACK_ERROR_SLAW;
	}
	else if(temp8 == 0x30)  //Check if Data was sent but NACK was received
	{
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status & (1 << TWSTO)) != 0); //Wait for stop = 0

		return NACK_ERROR_DATA;
	}
	else if(temp8 == 0x38)  //Check if arbitration lost in SLA+W or Data bytes
	{
		//Stop transfer here, SDA is low when it should be high
		//Super weird if we get this, since no other masters on line
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status & (1 << TWSTO)) != 0); //Wait for stop = 0

		return ARBITRATION_ERROR;
	}

	//CHECK A FEW MORE IN THE TRANSMIT STATUS CODES HERE
	//"programmer may wish to use state programming techniques for determining the state, status and action



	return SUCCESS;
}


uint8_t TWI_Master_Receive(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array)
{
	uint8_t status;
	uint8_t temp8;
	uint8_t send_value;
	
	//first send Slave address + R bit
	send_value = (slave_addr << 1) | 0x01;

	//Start TWI Communication
	*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));


	//Wait for TWINT to be set, meaning command has been sent
	do
	{
		status = *(TWI_addr + TWCR);
	} while ((status & 0x80) == 0);

	//Read status code to determine next steps
	temp8 = (*(TWI_addr + TWSR) & 0xF8);

	//Check that start signal or repeated Start was sent then send SLA+R
	if ((temp8 == 0x08) || (temp8 == 0x18))
	{
		*(TWI_addr + TWDR) = send_value;
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWEN));
	}
	else
	{
		return temp8;
	}


	//Read Status and check for ACK or NACK from slave
	temp8 = (*(TWI_addr + TWSR) & 0xF8);

	//Check if SLA+R sent and ACK received
	if(temp8 == 0x40)
	{
		//send stop condition (NACK) if only 1 byte is received
		if (num_bytes == 1)
		{
			*(TWI_addr+TWCR) = ((1<<TWINT) | (0<<TWEA) | (1<<TWEN));
		}
		else
		{
			*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWEA) | (1 << TWEN));
		}
	}
	else if(temp8 == 0x48)  //check is SLA+R sent and NACK received
	{
		//Stop communication, assuming slave thinks we are in write mode
		*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status & (1 << TWSTO)) != 0); //Wait for stop = 0

		return NACK_ERROR_REC_ON_R;
	}

	//While loop sends data bytes until all bytes are sent or error
	uint16_t index = 0;
	while (num_bytes != 0)
	{

		//wait until TWINT is set, command is done sending
		do
		{
			status = *(TWI_addr + TWCR);
		} while ((status & 0x80) == 0);

		//Read status code to determine next steps
		temp8 = (*(TWI_addr + TWSR) & 0xF8);

		//Check if Data received and ACK sent
		if(temp8 == 0x50)
		{
			//record data received
			num_bytes--;
			array[index] = *(TWI_addr + TWDR);
			index++;

			//send stop condition (NACK) if only 1 byte is received
			if (num_bytes == 1)
			{
				*(TWI_addr + TWCR) = ((1 << TWINT) | (0 << TWEA) | (1 << TWEN));
			}
			else
			{
				*(TWI_addr + TWCR) = ((1 << TWINT) | (1 << TWEA) | (1 << TWEN));
			}

		}
		else if(temp8 == 0x58)  //Check if Data was received and NACK Sent 
		{
			//record data received
			num_bytes--;
			array[index] = *(TWI_addr + TWDR);
			index++;

			*(TWI_addr + TWCR) = ((1 << TWINT) | (0<<TWEA) | (1 << TWEN));

		}


	}
	return status;
}