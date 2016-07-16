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
#include <string.h>

#include "crc.h"
#include "bit_manipulation.h"

/**
 *  Calculates CRC based con crc_params_t parameters using the "slow" algorithm
 *  For Ethertnet (IEEE 802.3) parameters should be as follow
 *   
 *  crc_params.type = CRC32;
 *  crc_params.poly.poly_crc32 = 0x04C11DB7;
 *  crc_params.crc_init.crc32 = 0xFFFFFFFF;
 *  crc_params.flags = CRC_OUTPUT_REVERSAL | CRC_OUTPUT_INVERSION | CRC_INPUT_REVERSAL;
 *
 *  @return crc_t object which contains the final remainder
 */
crc_t 
crc_slow(crc_params_t *crc_params, uint8_t *message, uint32_t msg_len)
{
    uint32_t i,j;
    uint8_t current_bit, _xor;
    crc_t crc_tmp; 

    /* Temporary CRC initialized according to crc_params */
    memcpy(&crc_tmp, &crc_params->crc_init, sizeof(crc_tmp));

    for(j=0; j<msg_len; j++)
    {
        for(i=0; i<8; i++)
        {
            if(crc_params->flags & CRC_INPUT_REVERSAL)
                current_bit = (message[j] >> i) & 0x1;
            else
                current_bit = (message[j] >> (7-i)) & 0x1;

            _xor = (get_bit(&crc_tmp, crc_params->type, 31) ^ current_bit);
            shift_left(&crc_tmp, crc_params->type, 1);
            if(_xor == 1)
                xor(&crc_tmp, &crc_params->poly, crc_params->type);
        }
    }
    
    if(crc_params->flags & CRC_OUTPUT_REVERSAL)
        reverse(&crc_tmp, crc_params->type);

    if(crc_params->flags & CRC_OUTPUT_INVERSION)
        invert(&crc_tmp, crc_params->type);

    return crc_tmp;
}

uint32_t
crc32_fast(uint8_t *message, uint32_t msg_len)
{
    uint32_t j;
    uint32_t remainder = 0xFFFFFFFF;
    for(j=0; j<msg_len; j++)
        remainder = crc32_table[message[j] ^ (remainder & 0xFF)] ^ (remainder >> 8);
    
    return reflect32(remainder);
}

