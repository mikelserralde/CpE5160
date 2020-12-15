/*
 * Hardware_Timeout.h
 *
 * Created: 11/22/2020 10:10:57 PM
 *  Author: ryoun
 */ 


#ifndef HARDWARE_TIMEOUT_H_
#define HARDWARE_TIMEOUT_H_
uint8_t Hardware_Timeout_Start(uint8_t volatile *TC_addr, uint16_t interval_ms);
uint8_t Hardware_Timeout_Check(uint8_t volatile *TC_addr);
void Hardware_Timeout(uint8_t volatile *TC_addr, uint16_t delay_ms);


#endif /* HARDWARE_TIMEOUT_H_ */