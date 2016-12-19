#ifndef __BIT_MANIPULATION_H__
#define __BIT_MANIPULATION_H__

#include <stdint.h> 
void invert(void *payload, uint8_t bit_size);
void reverse(void *payload, uint8_t bit_size);
void shift_left(void *payload, uint8_t bit_size, uint32_t shift_len);
void xor(void *payload, void *mask, uint8_t bit_size);
uint8_t get_bit(void *payload, uint8_t bit_size, uint8_t bitno);

uint32_t reflect32(uint32_t in_byte);
uint8_t reflect8(uint8_t in_byte);

#endif
