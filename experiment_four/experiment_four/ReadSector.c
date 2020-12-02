#include <stdio.h>
#include "Control_Outputs.h"
#include "ReadSector.h"
#include "SDCard.h"
#include "Directory_Functions_struct.h"
#include "board.h"

uint8_t Read_Sector(uint32_t sector_number, uint16_t sector_size, uint8_t * data_array)
{
	uint8_t SDtype;
	uint8_t error_flag;

	SDtype=Return_SD_Card_Type(); // HC=0, no change to sector number

	// SC=9, multiplies sector number by 512 to convert to byte addr.

	Output_Clear(&PB,SD_CS);  //nCS0=0;
	error_flag=Send_Command(17,(sector_number<<SDtype));


	Output_Set(&PB,SD_CS);  // nCS0=1;

	if(error_flag==no_errors)
		error_flag=Read_Block(sector_size,data_array);

	if(error_flag!=no_errors)
	{
		error_flag=Disk_Error;
	}

	return error_flag;
}