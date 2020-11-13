/*
 * TWI.h
 *
 * Created: 11/11/2020 
 *  Author: Hayden Long and Mikel Serralde
 */ 


#ifndef TWI_H_
#define TWI_H_

//Error Messages
#define LOW_CLOCK_FREQ			0
#define RECALC_PRESCALE			1
#define NACK_ERROR_SLAW			2
#define NACK_ERROR_DATA			3
#define ARBITRATION_ERROR		4
#define NACK_ERROR_REC_ON_R		5
#define SUCCESS 0xFF

//Register Bits
//TWCR
#define TWINT	7
#define TWEA	6
#define TWSTA	5
#define TWSTO	4
#define TWEN	2



/*
INPUTS: TWI peripheral base address, desired clock rate
RETURNS: Error message or success
FUNCTION: Sets the clock rate for the TWI / I2C transfers
*/
uint8_t TWI_Init(uint8_t volatile *TWI_addr, uint32_t clock_rate);

/*
INPUTS: TWI peripheral base address, desired slave address, number of bytes 
	to send, an array that contains the bytes to be sent
RETURNS: Error message or success
FUNCTION: Sends array of bytes to an address on the slave device
*/
uint8_t TWI_Master_Transmit(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array);

/*
INPUTS: TWI peripheral base address, desired slave address, number of bytes
	to receive, an array that records data received
RETURNS: Error message or success
FUNCTION: Receives num_bytes bytes from a specified slave device
	and stores the data in an array
*/
uint8_t TWI_Master_Receive(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array);



#endif //TWI_H_