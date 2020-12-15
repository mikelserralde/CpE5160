#include "board.h"
#include "SDCard.h"
#include "Control_Outputs.h"
#include "Read_Sector.h"
#include "stdio.h"




uint8_t Read_Sector(uint32_t sector_number, uint16_t sector_size, uint8_t * array_for_data)
{
	uint8_t SDtype,error_flag=No_Disk_Error;   

	//SDtype=Return_SD_Card_Type();
	Output_Clear(&PB,SD_CS);  // Clear nCS = 0
    error_flag=Send_Command(17,(sector_number<<0));
    if(error_flag==no_errors) error_flag=Read_Block(sector_size,array_for_data);
    Output_Set(&PB,SD_CS);  // Set nCS = 1

	if(error_flag!=no_errors)
	{
       error_flag=Disk_Error;
    }
    return error_flag;
}
