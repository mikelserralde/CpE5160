/*
 * STA013.h
 *
 * Created: 11/11/2020 
 *  Author: Hayden Long and Mikel Serralde
 */ 

#include <stdint.h>


#ifndef STA013_H_
#define STA013_H_

// Configuration function
uint8_t STA013_Config(uint8_t volatile* TWI_addr);

#endif //STA013_H_