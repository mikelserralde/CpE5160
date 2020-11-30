
///////////////////////////////////////////////////////////////////////////
/*
  _______ ____     _____   ____  
 |__   __/ __ \   |  __ \ / __ \ 
    | | | |  | |  | |  | | |  | |
    | | | |  | |  | |  | | |  | |
    | | | |__| |  | |__| | |__| |
    |_|  \____/   |_____/ \____/ 
	
//	FOR HAYDEN LONG

#define all of the offsets in the function below. Mikel is too lazy to do it :p

also look at all comments that have this: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Also, .h file is missing functions, I'm too lazy


// For Mikel
MBR_RelativeSectors is used incorrectly.
Look at 4a in the procedure.
Should read the BPB into SRAM, not treat it relatively.

*///////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include "FileSystem.h"
#include "SDCard.h"
#include "Directory_Functions_struct.h"

FS_values_t*Drive_p;
Drive_p = Export_Drive_values();

uint8_t read_value_8(uint16_t offset, uint8_t *array_name)
{
	uint8_t temp8;
	temp8 = *(array_name+offset);
	return temp8;
}

// FOR HAYDEN LONG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Look at lecture 18f, he gives us the correct function for read_value_32
// I am assuming read_value_16 acts the same way, but check me on it.
uint16_t read_value_16(uint16_t offset, uint8_t *array_name)
{
	uint16_t return_val = 0;
	uint8_t temp;
	uint8_t	i;
	
	for(i=0;i<2;i++)
	{   
		temp = *(array_name + offset + (1-i));
		return_val = return_val<<8;
		return_val |= temp;
	}
	
	return return_val;
}

uint32_t read_value_32(uint16_t offset, uint8_t *array_name)
{
	uint32_t return_val = 0;
	uint8_t temp;
	uint8_t	i;
	
	for(i=0;i<4;i++)
	{   
		temp = *(array_name + offset + (3-i));
		return_val = return_val<<8;
		return_val |= temp;
	}
	
	return return_val;
}

uint8_t mount_drive(uint8_t * array)
{
	uint8_t result;
	uint32_t MBR_RelativeSectors = 0;
	uint32_t FATSz;
	uint32_t TotSec;
	uint32_t DataSec;
	uint32_t CountofClusters;
	// Step 1: Read Block 0
	result = Read_Block(0, &array);
	if( (*(array+0) != 0xEB) && (*(array+0) != 0xE9) )
	{
		MBR_RelativeSectors = *(array+0x001C6);
	}
	
	if((*(array+0x0000+MBR_RelativeSectors) != 0xEB) && (*(array+0x0000+MBR_RelativeSectors) != 0xE9))
	{
		return BPB_NOT_FOUND;
	}
	
	Drive_p->BytesPerSec = *(array+0x000B+MBR_RelativeSectors);
	Drive_p->SecPerClus = *(array+0x000D+MBR_RelativeSectors);
	
	// Step 2: Determine # of Sectors in Root Dir
	// Should be 0 for FAT32
	// FOR HAYDEN LONG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Idk what the max value for this can be if it's FAT16, but I made it 32 bit just in case
	Drive_p->RootDirSecs = ((BPB_RootEntCnt * 32) + (Drive_p->BytesPerSec - 1)) / (Drive_p->BytesPerSec);
	
	
	// Step 3: Find # of data sectors
	if(*(array+0x0016+MBR_RelativeSectors) != 0)
		FATSz = *(array+0x0016+MBR_RelativeSectors);
	else
		FATSz = *(array+0x0024+MBR_RelativeSectors);
	
	if(*(array+0x0013+MBR_RelativeSectors) != 0)
		TotSec = *(array+0x0013+MBR_RelativeSectors);
	else
		TotSec = *(array+0x0020+MBR_RelativeSectors);
	
	// DataSec = BPB_TotSec32 – (BPB_ResvdSecCnt+(BPB_NumFATs*BPB_FATSz32)+RootDirSectors)
	DataSec = TotSec – (*(array+ 0x000E + MBR_RelativeSectors)+((array+0x0010+MBR_RelativeSectors)*FATSz)+Drive_p->RootDirSecs);
	
	// Step 4: Determine FAT Type and Count of Clusters
	CountofClusters = DataSec / Drive_p->SecPerClus;
	
	if(CountofClusters < 4085)
	{
		Drive_p->FATtype = FAT_Type12;
	} else if(CountofClusters < 65525)
	{	
		Drive_p->FATtype = FAT_Type16;
		
	} else
	{
		Drive_p->FATtype = FAT_Type32;
		
	}
	// Step 5: Determine the First Sector of FAT
	// ThisFATSecNum = BPB_ResvdSecCnt + (FATOffset / BPB_BytsPerSec) 
	// FATOffset = 0
	// ThisFATSecNum = *(array+ 0x000E + MBR_RelativeSectors);
	// StartofFAT = = BPB_ResvdSecCnt + MBR_RelativeSectors
	Drive_p->StartofFAT = *(array+ 0x000E + MBR_RelativeSectors) + MBR_RelativeSectors;
	
	// Step 6: Determine First Sector
	// FirstDataSector = BPB_ResvdSecCnt + (BPB_NumFATs*FATSz) + RootDirSectors + MBR_RelativeSectors
	Drive_p->FirstDataSec = *(array+ 0x000E + MBR_RelativeSectors) + (*(array+ 0x0010 + MBR_RelativeSectors) * FATSz) + Drive_p->RootDirSecs + MBR_RelativeSectors;

	// Step 7: Determine FirstRootDirSecNum
	if(Drive_p->FATtype == FAT_Type16)
	{
		// FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs*FATSz) + MBR_RelativeSectors
		Drive_p->FirstRootDirSec = *(array+ 0x000E + MBR_RelativeSectors) + (*(array+ 0x0010 + MBR_RelativeSectors) * FATSz) + MBR_RelativeSectors;
	}
	else
	{
		// FirstRootDirSecNum = ((BPB_RootClus-2)*BPB_SecPerClus)+FirstDataSec
		Drive_p->FirstRootDirSec =  ((*(array+ 0x002C + MBR_RelativeSectors) - 2) * Drive_p->SecPerClus) + Drive_p->FirstDataSec;
	}
}


uint32_t First_Sector(uint32_t cluster_num)
{
	if(cluster_num != 0)
		return (((cluster_num - 2) * Drive_p->SecPerClus) + Drive_p->FirstDataSec);
	else
		return Drive_p->FirstRootDirSec;
}

uint32_t Find_Next_Clus(uint32_t cluster_num, uint8_t * array)
{
	uint32_t sector_num;
	uint32_t cluster;
	// Step 1: Determine the FAT sector number for the cluster
	sector_num = ((cluster_num*Drive_p->FATtype) / Drive_p->BytesPerSec) + Drive_p->StartofFAT;
	
	// Step 2: Read the FAT sector into SRAM
	Read_Sector(sector_num, Drive_p->BytesPerSec, &array);
	
	// Step 3: Determine the offset of the cluster within this sector
	FATOffset = (uint16_t)((cluster_num*Drive_p->FATtype)%(Drive_p->BytesPerSec));
	
	// Step 4: Read cluster entry from FAT sector in SRAM
	if(Drive_p->FATtype == FAT_Type32)
		cluster = (read_value_32(FATOffset, &array)&0x0FFFFFFF);
	else
		cluster = (uint32_t)(read_value_16(FATOffset, &array);
	
	return cluster;
}