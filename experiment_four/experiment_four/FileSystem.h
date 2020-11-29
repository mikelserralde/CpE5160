#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

uint8_t read_value_8(uint16_t offset, uint8_t *array_name);

uint16_t read_value_16(uint16_t offset, uint8_t *array_name);

uint32_t read_value_32(uint16_t offset, uint8_t *array_name);

#endif //FILE_SYSTEM_H_