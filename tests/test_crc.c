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
#include <string.h>
#include <stdio.h>
#include "test.h"
#include "../crc.h"

extern uint8_t *_binary_test1_start;
extern uint8_t *_binary_test2_start;
extern uint8_t *_binary_test3_start;

typedef struct {
    uint8_t *buffer;
    uint32_t len;
    uint32_t crc32;

} testcase;

uint32_t 
test_crc32_returns_correct_value(testcase* test)
{
    uint32_t temp = crc32_ethernet(crc32(test->buffer, test->len));
    _assert(temp == test->crc32);
    return 0;
}

uint32_t
test_crc32_fast_returns_same_result_as_crc32(testcase* test)
{

    _assert(crc32_ethernet(crc32(test->buffer, test->len)) == 
            crc32_ethernet(crc32_fast(test->buffer, test->len)));
    return 0;


}

void 
compute_crc32_table() 
{
    uint8_t temp = 0;
    while(temp != 255)
    {
        if(temp % 4 == 0)
            printf("\n");
        
        printf("0x%.8x, ", crc32(&temp, 1));
        ++temp;
    }
    printf("0x%.8x, ", crc32(&temp, 1));
}


int
main(int argc, char *argv[])
{

    testcase test1 = {
        .buffer = (uint8_t*)&_binary_test1_start,
        .len = 60,
        .crc32 = 0x11d056c3,
    };
    
    testcase test2 = {
        .buffer = (uint8_t*)&_binary_test2_start,
        .len = 60,
        .crc32 = 0xbb327374,
    };
   
    testcase test3 = {
        .buffer = (uint8_t*)&_binary_test3_start,
        .len = 60,
        .crc32 = 0x3e869219,
    };
    
    //compute_crc32_table();
    test_crc32_returns_correct_value(&test1);
    test_crc32_returns_correct_value(&test2);
    test_crc32_returns_correct_value(&test3);
    test_crc32_fast_returns_same_result_as_crc32(&test1);
    test_crc32_fast_returns_same_result_as_crc32(&test2);
    test_crc32_fast_returns_same_result_as_crc32(&test3);
    return 0;
}
