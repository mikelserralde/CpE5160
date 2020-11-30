#include <stdio.h>
#include "FileSystem.h"
#include "SDCard.h"
#include "Directory_Functions_struct.h"

uint8_t read_value_8(uint16_t offset, uint8_t *array_name)
{
	uint8_t temp8;
	temp8 = *(array_name+offset);
	return temp8;
}

uint16_t read_value_16(uint16_t offset, uint8_t *array_name)
{
	uint16_t temp16;
	temp16 = *(array_name+offset);
	return temp16;
}

uint32_t read_value_32(uint16_t offset, uint8_t *array_name)
{
	uint32_t temp32;
	temp32 = *(array_name+offset);
	return temp32;
}

//uint8_t mount_drive(void);
uint8_t mount_drive(uint8_t * array)
{
//	uint8_t array??
	// Step 1: Read Block 0
	Read_Block(0, array?);
	
}