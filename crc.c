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

#ifdef __KERNEL__
#include <linux/string.h>
#include <linux/types.h>
#else
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#endif

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

/**
 * Returns the proper CRC table according to CRC parameters
 */
void*
get_crc_table(crc_params_t *crc_params)
{
    /* Only CRC32 supported for now */
    assert(crc_params->type == CRC32);

    if(crc_params->type == CRC32) 
        return (void*)crc32_table;

    /* Not supported */
    assert(0);
    return NULL;
}


crc_t
crc_fast(crc_params_t *crc_params, uint8_t *message, uint32_t msg_len)
{
    crc_t crc_tmp; 
    uint32_t j;
    void *t;

    /* Temporary CRC initialized according to crc_params */
    memcpy(&crc_tmp, &crc_params->crc_init, sizeof(crc_tmp));
    
    if(crc_params->type == CRC32)
        t = ((uint32_t*)get_crc_table(crc_params));
   
     for(j=0; j<msg_len; j++)
    {
        if(crc_params->type == CRC32)
        {
            if(crc_params->flags & CRC_INPUT_REVERSAL)
                crc_tmp.crc32 = 
                ((uint32_t*)t)[reflect8(message[j]) ^ ((crc_tmp.crc32 >> 24) & 0xFF)] ^ 
                                (crc_tmp.crc32 << 8);
            else
                crc_tmp.crc32 = 
                ((uint32_t*)t)[message[j] ^ ((crc_tmp.crc32 >> 24) & 0xFF)] ^ 
                                (crc_tmp.crc32 << 8);
        }
        else
        {
            /* Not supported */
            assert(0);
        }
    }
    
    if(crc_params->flags & CRC_OUTPUT_REVERSAL)
        reverse(&crc_tmp, crc_params->type);

    if(crc_params->flags & CRC_OUTPUT_INVERSION)
        invert(&crc_tmp, crc_params->type);

    return crc_tmp;
}
