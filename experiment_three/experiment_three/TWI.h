/*
 * TWI.h
 *
 * Created: 11/11/2020 
 *  Author: Hayden Long and Mikel Serralde
 */ 


#ifndef TWI_H_
#define TWI_H_


void TWI_Init(uint8_t volatile *TWI_addr, uint32_t clock_rate);


uint8_t TWI_Master_Transmit(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array);


uint8_t TWI_Master_Receive(uint8_t volatile* TWI_addr, uint8_t slave_addr,
	uint16_t num_bytes, uint8_t* array);



#endif //TWI_H_