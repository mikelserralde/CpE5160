#include <stdio.h>
#include "board.h"
#include "UART.h"
#include "UART_Print.h"
#include "SPI.h"
#include "SDCard.h"
#include "File_System_v2.h"
#include "print_memory.h"
#include "Directory_Functions_struct.h"
#include "Read_Sector.h"
#include <avr/pgmspace.h>
#include "player_ISR.h"
//#include "Play_Song.h"

/******* Private Constants *************/
#define CR (0x0D)
#define LF (0x0A)







// Read Value Functions

/***********************************************************************
DESC: Reads a specified byte from a block of memory 
INPUT: Offset to the byte, Starting address of the block of memory
RETURNS: uint8_t specifed byte
CAUTION: 
************************************************************************/
uint8_t read_value_8(uint16_t offset, uint8_t * array_name)
{
   uint8_t return_val;
   uint8_t prnt_bffr[15];
   offset&=0x1FF;  // limit offset to 0 to 511
   return_val=*(array_name+offset);
   //sprintf(prnt_bffr,"%u\n\r",return_val);
   //UART_Transmit_String(&UART1,0,prnt_bffr);
   return return_val;
}

/***********************************************************************
DESC: Reads a specified integer (stored little endian) from a block of memory 
INPUT: Offset to the LSB of the integer, Starting address of the block of memory
RETURNS: uint16_t specfied integer
CAUTION: 
************************************************************************/

uint16_t read_value_16(uint16_t offset, uint8_t * array_name)
{
   uint16_t return_val;
   uint8_t prnt_bffr[15];
   uint8_t temp8;
   return_val=0;
   offset&=0x1FF;  // limit offset to 0 to 511
   return_val=*(array_name+offset+1);
   return_val=(return_val<<8);
   temp8=*(array_name+offset);
   return_val|=temp8;
   //sprintf(prnt_bffr,"%u\n\r",return_val);
   //UART_Transmit_String(&UART1,0,prnt_bffr);
   return return_val;
}

/***********************************************************************
DESC: Reads a specified word (stored little endian) from a block of memory 
INPUT: Offset to the LSB of the word, Starting address of the block of memory
RETURNS: uint32_t specfied word
CAUTION: 
************************************************************************/

uint32_t read_value_32(uint16_t offset, uint8_t * array_name)
{
   uint32_t return_val;
   uint8_t prnt_bffr[15];
   uint8_t temp8;
   offset&=0x1FF;  // limit offset to 0 to 511
   return_val=*(array_name+offset+3);
   return_val=(return_val<<8);
   temp8=*(array_name+offset+2);
   return_val|=temp8;
   return_val=(return_val<<8);
   temp8=*(array_name+offset+1);
   return_val|=temp8;
   return_val=(return_val<<8);
   temp8=*(array_name+offset);
   return_val|=temp8;
   //sprintf(prnt_bffr,"%u\n\r",return_val);
   //UART_Transmit_String(&UART1,0,prnt_bffr);
   return return_val;
}

const char Mnt_Drv_1[26] PROGMEM = {"Locating Boot Sector...\n\r"};
const char Mnt_Drv_2[20] PROGMEM = {"Relative Sectors = "};  
const char Mnt_Drv_3[14] PROGMEM = {"Disk Error!\n\r"}; 
const char Mnt_Drv_4[20] PROGMEM = {"FAT16 Detected...\n\r"}; 
const char Mnt_Drv_5[20] PROGMEM = {"FAT32 Detected...\n\r"};  
const char Mnt_Drv_6[14] PROGMEM = {"StartofFAT = "};
const char Mnt_Drv_7[16] PROGMEM = {"FirstDataSec = "};
const char Mnt_Drv_8[20] PROGMEM = {"Relative Sectors = "};

/***********************************************************************
DESC: Determines FAT type, Start of the FAT, Root Directory Sector
      and Start of Data for an SD card
INPUT: Start of a block of memory in xdata that can be used 
       to read blocks from the SD card
RETURNS: uint8_t error code    Creates globals in idata for: 
idata uint32_t FATSz, RelSec, RootClus, FirstDataSec, StartofFAT;
idata uint16_t BytesPerSec, BytesPerSecM, RootEntCnt;
idata uint8_t SecPerClus, FATtype, SecShift;

CAUTION: 
************************************************************************/

uint8_t Mount_Drive(uint8_t * array_in)
{
  uint32_t TotSec, DataSec, CntClus,MBR_RelSec, FATSz, RootClus;
  uint16_t RsvdSecCnt, RootEntCnt, temp16;
  uint8_t NumFAT, temp8;
  uint8_t *values,*prnt_bffr;
  FS_values_t * Drive_p;

   Drive_p=Export_Drive_values();
   MBR_RelSec=0;
   RootClus=0;
   values=array_in;
   //PORTLED |= (1 << PORTLED_AMBER);
   prnt_bffr=Export_print_buffer();
   
   Copy_String_to_Buffer(Mnt_Drv_1,0,prnt_bffr);
   UART_Transmit_String(&UART1,0,prnt_bffr);
   //printf("Locating Boot Sector...\n\r");
   Read_Sector(0,512,values);
   //print_memory(&UART1,512,values);
   temp8=read_value_8(0,values);
   if((temp8!=0xEB)&&(temp8!=0xE9))
   {
      MBR_RelSec=read_value_32(MBR_RelSectors,values);
	  Read_Sector(MBR_RelSec,512,values);
	  Copy_String_to_Buffer(Mnt_Drv_2,0,prnt_bffr);
	  UART_Transmit_String(&UART1,0,prnt_bffr);
	  sprintf(prnt_bffr,"%lu\n\r",MBR_RelSec);
	  UART_Transmit_String(&UART1,0,prnt_bffr);
	  temp8=read_value_8(0,values); 
   }
   if((temp8!=0xEB)&&(temp8!=0xE9))
   {
      Copy_String_to_Buffer(Mnt_Drv_3,0,prnt_bffr);
      UART_Transmit_String(&UART1,0,prnt_bffr);
	  //printf("Disk Error!\n\r");
	  return Disk_Error;
   }
   Drive_p->BytesPerSec=read_value_16(BPB_BytesPerSector,values);
   Drive_p->BytesPerSecShift=0;
   temp16=Drive_p->BytesPerSec;
   while(temp16!=0x01)
   {
      Drive_p->BytesPerSecShift++;
      temp16=temp16>>1;
   }
   Drive_p->SecPerClus=read_value_8(BPB_SectorsPerCluster,values);
   RsvdSecCnt=read_value_16(BPB_RsvdSectorCount,values);
   NumFAT=read_value_8(BPB_NumberFATs,values);
   RootEntCnt=read_value_16(BPB_RootEntryCount,values);
   TotSec=read_value_16(BPB_TotalSectors16,values);
   if(TotSec==0) TotSec=read_value_32(BPB_TotalSectors32,values);
   FATSz=read_value_16(BPB_FATsize16,values);
   if(FATSz==0)
   {
	  FATSz=read_value_32(BPB_FATsize32,values);
      RootClus=read_value_32(BPB_RootCluster,values);
   }
   Drive_p->RootDirSecs=((RootEntCnt * 32) + (Drive_p->BytesPerSec - 1))/Drive_p->BytesPerSec;
   DataSec=TotSec-(RsvdSecCnt+(NumFAT*FATSz)+Drive_p->RootDirSecs);
   CntClus=DataSec/Drive_p->SecPerClus;
   Drive_p->StartofFAT=RsvdSecCnt+MBR_RelSec;
   Copy_String_to_Buffer(Mnt_Drv_6,0,prnt_bffr);
   UART_Transmit_String(&UART1,0,prnt_bffr);
   sprintf(prnt_bffr,"%lu\n\r",Drive_p->StartofFAT);
   UART_Transmit_String(&UART1,0,prnt_bffr);
   Drive_p->FirstDataSec=Drive_p->StartofFAT+(NumFAT*FATSz)+Drive_p->RootDirSecs;
   Copy_String_to_Buffer(Mnt_Drv_7,0,prnt_bffr);
   UART_Transmit_String(&UART1,0,prnt_bffr);
   sprintf(prnt_bffr,"%lu\n\r",Drive_p->FirstDataSec);
   UART_Transmit_String(&UART1,0,prnt_bffr);
   if(CntClus<65525)
   {
     Drive_p->FATtype=FAT16;
	 Drive_p->FATshift=FAT16_shift;
	 Copy_String_to_Buffer(Mnt_Drv_4,0,prnt_bffr);
	 UART_Transmit_String(&UART1,0,prnt_bffr);
	 //printf("FAT16 Detected...\n\r");
	 Drive_p->FirstRootDirSec=Drive_p->StartofFAT+(NumFAT*FATSz);
   }
   else
   {
     Drive_p->FATtype=FAT32;
	 Drive_p->FATshift=FAT32_shift;
	 Copy_String_to_Buffer(Mnt_Drv_5,0,prnt_bffr);
	 UART_Transmit_String(&UART1,0,prnt_bffr);
	 //printf("FAT32 Detected...\n\r");  
     Drive_p->FirstRootDirSec=((RootClus-2)*Drive_p->SecPerClus)+Drive_p->FirstDataSec;
   }
   Copy_String_to_Buffer(Mnt_Drv_8,0,prnt_bffr);
   UART_Transmit_String(&UART1,0,prnt_bffr);
   sprintf(prnt_bffr,"%lu\n\r",Drive_p->FirstRootDirSec);
   UART_Transmit_String(&UART1,0,prnt_bffr);
   return No_Disk_Error;
}


/***********************************************************************
DESC: Calculates the First Sector of a given Cluster 
INPUT: uint32_t Cluster number
RETURNS: uint32_t sector number 
CAUTION: 
************************************************************************/
uint32_t First_Sector (uint32_t Cluster_num)
{
   uint32_t Sector_num;
   FS_values_t * Drive_p;

   Drive_p=Export_Drive_values();
   if(Cluster_num==0) 
   {
       Sector_num=Drive_p->FirstRootDirSec;
   }
   else
   {
       Sector_num=((Cluster_num-2)*Drive_p->SecPerClus)+Drive_p->FirstDataSec;
   }
   return Sector_num;
}





/***********************************************************************
DESC: Finds the next cluster number of a file in the FAT with an input
      parameter of the current cluster number.
INPUT: Current cluster number.
RETURNS: Next Cluster number from the FAT
CAUTION: 
************************************************************************/


uint32_t Find_Next_Clus(uint32_t Cluster_num, uint8_t * array_name)
{
   uint32_t Sector, return_clus=0;
   uint16_t FAToffset;
   uint8_t * values;
   FS_values_t * Drive_p;

   Drive_p=Export_Drive_values();
   values=array_name;
   Sector=(Cluster_num>>(Drive_p->BytesPerSecShift-Drive_p->FATshift))+Drive_p->StartofFAT;
   Read_Sector(Sector, Drive_p->BytesPerSec,values);
   FAToffset=(uint16_t)((Cluster_num<<Drive_p->FATshift)&(Drive_p->BytesPerSec-1));
   if(Drive_p->FATtype==FAT32)    // FAT32
   {
       return_clus=(read_value_32(FAToffset,values)&0x0FFFFFFF);
   }
   else if(Drive_p->FATtype==FAT16)    // FAT16
   {
       return_clus=(uint32_t)(read_value_16(FAToffset,values));
	   if(return_clus==0x0000FFFF) return_clus=0x0FFFFFFF; // EOF for FAT16 changed to EOF for FAT32
   }
   return return_clus;
}
   



/***********************************************************************
DESC: Prints the sectors of a file until the user hits X
      Prints the Cluster Number and Sector number of each sector as well
INPUT: Starting Cluster of the file and the start of a 
block of memory in xdata that can be used to read blocks from the SD card
RETURNS: uint8_t 0
CAUTION: 
************************************************************************/


uint8_t Open_File(uint32_t Cluster_num, uint8_t * array_in)
{
   uint32_t Sector=0, SecOffset;
   uint8_t temp8;
   uint8_t * values;
   uint8_t *prnt_bffr;
   FS_values_t * Drive_p;

   Drive_p=Export_Drive_values();
   prnt_bffr=Export_print_buffer();
   values=array_in;
   SecOffset=0;
   
   
   do
   {
      if(SecOffset==0) Sector=((Cluster_num-2)*Drive_p->SecPerClus)+Drive_p->FirstDataSec;
      sprintf(prnt_bffr,"Cluster#: %9lu,  Sector#: %9lu,  SecOffset: %lu\n\r",Cluster_num,(Sector+SecOffset),SecOffset);
      UART_Transmit_String(&UART1,0,prnt_bffr);
	  Read_Sector((Sector+SecOffset), Drive_p->BytesPerSec, values);      
      print_memory(&UART1,512,values);
      SecOffset++;
      if(SecOffset==Drive_p->SecPerClus)
      {
         Cluster_num=Find_Next_Clus(Cluster_num,values);
         SecOffset=0;
      }
      sprintf(prnt_bffr,"Press Space to Continue or X to exit\n\r");
	  UART_Transmit_String(&UART1,0,prnt_bffr);
      do
      {
        temp8=UART_Receive(&UART1);
      }while((temp8!=0x20)&&(temp8!='X')&&(temp8!='P'));
      if(temp8=='P')
      {
         Play_MP3_file(Cluster_num);
		 //Play_Song(Cluster_num);
      }
   }while(temp8==0x20);
   UART_Transmit(&UART1,CR);
   UART_Transmit(&UART1,LF);
   UART_Transmit(&UART1,LF);
return 0;
}




