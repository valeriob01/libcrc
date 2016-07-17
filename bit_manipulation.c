/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Author: Marco Guerri <gmarco.dev@gmail.com>
 */

#include <stdint.h>
#include <assert.h>

uint32_t 
reflect32(uint32_t in_byte) 
{
    uint32_t temp = 0;
    uint32_t i;
    for(i = 0; i < 16; i++ )
    {
        temp = temp | ((in_byte & (0x80000000 >> i)) >> (31-2*i))
                    | ((in_byte & (0x00000001 << i)) << (31-2*i));
    }
    return temp;
}

uint8_t 
reflect8(uint8_t in_byte)
{
    uint8_t temp = 0;
    uint8_t i;
    for(i = 0; i < 8; i++ )
    {
        temp = temp | ((in_byte & (0x80 >> i)) >> (7-2*i))
                    | ((in_byte & (0x01 << i)) << (7-2*i));
    }
    return temp;
}

/**
 * Inverts a payload of variable size
 */
void
invert(void *payload, uint8_t bit_size)
{

    assert(bit_size == 8 || 
           bit_size == 32);

    switch(bit_size) 
    {
        case 8:
            *((uint8_t*)payload) = ~*((uint8_t*)payload);
            break;
        case 32:
            *((uint32_t*)payload) = ~*((uint32_t*)payload);
            break;
    }
}


/**
 * Reverses a payload of variable size 
 */
void
reverse(void *payload, uint8_t bit_size)
{
    /* Not yet implemented for 16 bits */
    assert(bit_size == 8 || 
           bit_size == 32);

    switch(bit_size)
    {
        case 8:
            *((uint8_t*)payload) = reflect8(*((uint8_t*)payload));
            break;
        case 32:
            *((uint32_t*)payload) = reflect32(*((uint32_t*)payload));
            break;
    }
}


/** 
 * Shift left a payload of variable size 
 */
void 
shift_left(void *payload, uint8_t bit_size, uint32_t shift_len)
{
    assert(shift_len <= bit_size);
    assert(bit_size == 8 || bit_size == 16 || bit_size == 32);

    switch(bit_size)
    {
        case 8:
            *((uint8_t*)payload) = *((uint8_t*)payload) << shift_len;
            break;
        case 16:
            *((uint16_t*)payload) = *((uint16_t*)payload) << shift_len;
            break;
        case 32:
            *((uint32_t*)payload) = *((uint32_t*)payload) << shift_len;
            break;
    }
}


/**
 * XOR payload with a mask of variable size
 */
void
xor(void *payload, void *mask, uint8_t bit_size)
{
    assert(bit_size == 8 || bit_size == 16 || bit_size == 32);
    switch(bit_size)
    {
        case 8:
            *((uint8_t*)payload) = *((uint8_t*)payload) ^ *((uint8_t*)mask);
            break;
        case 16:
            *((uint16_t*)payload) = *((uint16_t*)payload) ^ *((uint16_t*)mask);
            break;
        case 32:
            *((uint32_t*)payload) = *((uint32_t*)payload) ^ *((uint32_t*)mask);
            break;
    }
}

/**
 *  Returns the value of a single bit, bitno is 0-indexed 
 */ 
uint8_t 
get_bit(void *payload, uint8_t bit_size, uint8_t bitno)
{
    assert(bitno < bit_size);
    assert(bit_size == 8  || bit_size == 16 || bit_size == 32);

    switch(bit_size)
    {
        case 8:
            return (*((uint8_t*)payload) >> bitno) & 0xFF;
        case 16:
            return (*((uint16_t*)payload) >> bitno) & 0xFF;
        case 32:
            return (*((uint32_t*)payload) >> bitno) & 0xFF;
    }

    /* Should not get here */
    assert(0);
}
