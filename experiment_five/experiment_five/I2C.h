#ifndef _I2C_H
#define _I2C_H

#include "board.h"




#define no_errors (0)
#define bus_busy_error (0x81)
#define NACK_error (0x82)

// ------ Public function prototypes -------------------------------
uint8_t TWI_Master_Init(uint8_t volatile *TWI_addr, uint32_t I2C_FREQ);
uint8_t TWI_Master_Transmit(uint8_t volatile *TWI_addr, uint8_t device_addr, uint32_t internal_addr, uint8_t int_addr_bytes, uint8_t num_bytes, uint8_t *send_array);
uint8_t TWI_Master_Receive(uint8_t volatile *TWI_addr, uint8_t device_addr, uint32_t internal_addr, uint8_t int_addr_bytes, uint8_t num_bytes, uint8_t *rec_array);





#endif