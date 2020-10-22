// sdcard.h
// by mikel

#ifndef SDCARD_H_
#define SDCARD_H_

// SD Commands
#define CMD0 0
#define CMD8 8
#define CMD17 17
#define CMD55 55
#define CMD58 58
#define ACMD41 41

// Return Values for SD Card Functions
#define TIMEOUT 0
#define ILLEGAL_COMMAND 1
#define UNEXPECTED_ACTIVE_STATE 2
#define UNEXPECTED_IDLE_STATE 3
#define CARD_CAPACITY_ERROR 4
#define VOLTAGE_ERROR 5
#define INACTIVE_CARD 6
#define SUCCESS 255
// If the return is not one of the above, it will be the R1 response with an error
// Otherwise, something is very wrong

// Sends a command to SD Card using SPI with a 32 bit argument
uint8_t Send_Command(uint8_t command, uint32_t argument);

// Receives the response of given size from the SD_Card after sending 0xFF
// Puts the response into the given array 
uint8_t Receive_Response(uint8_t number_of_bytes, uint8_t * array_name);

// Initializes the SD Card
uint8_t SD_Card_Init(void);

// Reads a block of data from the SD Card
uint8_t Read_Block(uint16_t number_of_bytes, uint8_t * array);

#endif // SDCARD_H_
