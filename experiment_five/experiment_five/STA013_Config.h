#ifndef _STA013_Config_H
#define _STA013_Config_H

#include "board.h"



#define STA013 (0x43)

// ------ Public function prototypes -------------------------------
void STA013_Reset_Init(void);

void STA013_Reset_Control(uint8_t control);

void STA013_BIT_EN_Init(void);

void STA013_BIT_EN_Control(uint8_t control);

void STA013_DATA_REQ_Init(void);

uint8_t STA013_Init(void);



#endif