#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#define FAT_Type32 4
#define FAT_Type16 1
#define FAT_Type12 2

// BPB Offsets
#define BS_jmpBoot 0
#define BPB_BytsPerSec 0x000B
#define BPB_SecPerClus 0x000D
#define BPB_ResvdSecCnt 0x000E
#define BPB_NumFATs 0x0010
#define BPB_TotSec16 0x0013
#define BPB_FATSz16 0x0016
#define BPB_TotSec32 0x0020
#define BPB_FATSz32 0x0024
#define BPB_RootClus 0x002C

// ERRORS
#define BPB_NOT_FOUND 0xCC
#define SUCCESS 0xFF


uint8_t read_value_8(uint16_t offset, uint8_t *array_name);

uint16_t read_value_16(uint16_t offset, uint8_t *array_name);

uint32_t read_value_32(uint16_t offset, uint8_t *array_name);

uint8_t mount_drive(uint8_t * array);

uint32_t First_Sector(uint32_t cluster_num);

uint32_t Find_Next_Clus(uint32_t cluster_num, uint8_t * array);

#endif //FILE_SYSTEM_H_