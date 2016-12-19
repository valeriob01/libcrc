/*
 * libcrc - Library which calculates CRC checksums
 *
 * Copyright (C) 2016 Marco Guerri <marco.guerri.dev@fastmail.com>
 *
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
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#include "test.h"
#include "../crc.h"

extern uint8_t *_binary___test1_bin_start;
extern uint8_t *_binary___test2_bin_start;
extern uint8_t *_binary___test3_bin_start;
extern uint8_t *_binary___test4_bin_start;
extern uint8_t *_binary___test5_bin_start;
extern uint8_t *_binary___test6_bin_start;

typedef struct {
    uint8_t *buffer;
    uint32_t len;
    uint32_t crc32;
} testcase;

uint32_t 
test_crc32_slow_returns_correct_value_for_ethernet(testcase* test)
{

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_OUTPUT_REVERSAL | CRC_OUTPUT_INVERSION | CRC_INPUT_REVERSAL;

    crc_t res = crc_slow(&crc_params, test->buffer, test->len);
    _assert(res.crc32 == test->crc32);
    return 0;
}


uint32_t
test_crc32_slow_input_reversal()
{
    
    char *message = "Nel mezzo del cammin di nostra vita";

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_INPUT_REVERSAL;
    
    crc_t res = crc_slow(&crc_params, (uint8_t*)message, strlen(message));
    _assert(res.crc32 == 0xE02C2025);
     
    return 0;
}


uint32_t
test_crc32_slow_output_reversal()
{
    
    char *message = "Nel mezzo del cammin di nostra vita";

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_OUTPUT_REVERSAL;

    crc_t res = crc_slow(&crc_params, (uint8_t*)message, strlen(message));
    _assert(res.crc32 == 0xAEC3A757);

    return 0;
}


uint32_t
test_crc32_slow_output_inversion()
{
    
    char *message = "Nel mezzo del cammin di nostra vita";

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_OUTPUT_INVERSION;

    crc_t res = crc_slow(&crc_params, (uint8_t*)message, strlen(message));
    _assert(res.crc32 == 0x151A3C8A);

    return 0;
}

uint32_t 
test_crc32_fast_returns_correct_value_for_ethernet(testcase* test)
{

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_OUTPUT_REVERSAL | CRC_OUTPUT_INVERSION | CRC_INPUT_REVERSAL;

    crc_t res = crc_fast(&crc_params, test->buffer, test->len);
    _assert(res.crc32 == test->crc32);
    return 0;
}


uint32_t
test_crc32_fast_input_reversal()
{
    
    char *message = "Nel mezzo del cammin di nostra vita";

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_INPUT_REVERSAL;
    
    crc_t res = crc_fast(&crc_params, (uint8_t*)message, strlen(message));
    _assert(res.crc32 == 0xE02C2025);
     
    return 0;
}


uint32_t
test_crc32_fast_output_reversal()
{
    
    char *message = "Nel mezzo del cammin di nostra vita";

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_OUTPUT_REVERSAL;

    crc_t res = crc_fast(&crc_params, (uint8_t*)message, strlen(message));
    _assert(res.crc32 == 0xAEC3A757);

    return 0;
}


uint32_t
test_crc32_fast_output_inversion()
{
    
    char *message = "Nel mezzo del cammin di nostra vita";

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_OUTPUT_INVERSION;

    crc_t res = crc_fast(&crc_params, (uint8_t*)message, strlen(message));
    _assert(res.crc32 == 0x151A3C8A);

    return 0;
}

uint32_t 
test_crc32_performance()
{

    struct timespec start, end;
    char result[128];

    uint8_t *buffer;
    const uint32_t buffer_len = 327680000;
    uint32_t i = 0;

    uint64_t ms, diff;

    buffer = (uint8_t*)malloc(buffer_len*sizeof(uint8_t));
    for(; i < buffer_len; i++)
        buffer[i] = rand() % 255;

    crc_params_t crc_params;
    crc_params.type = CRC32;
    crc_params.poly.poly_crc32 = 0x04C11DB7;
    crc_params.crc_init.crc32 = 0xFFFFFFFF;
    crc_params.flags = CRC_OUTPUT_REVERSAL | CRC_OUTPUT_INVERSION | CRC_INPUT_REVERSAL;

    /* First run, ignore result */
    crc_t res = crc_fast(&crc_params, buffer, buffer_len);

    /* Test runtime now */
    clock_gettime(CLOCK_MONOTONIC, &start);
    res = crc_fast(&crc_params, buffer, buffer_len);
    clock_gettime(CLOCK_MONOTONIC, &end); 
    
    diff = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
    ms = diff / 1000000L;
    snprintf(result, 128, "CRC: %x, SIZE %"PRIu32", TIME: %"PRIu64"\n", 
             res.crc32, 
             buffer_len, 
             ms);

    free(buffer);
    RESULT(result);
    return 0;
}

int
main(int argc, char *argv[])
{
    /* Test cases for real ethernet payloads */
    testcase test1 = {
        .buffer = (uint8_t*)&_binary___test1_bin_start,
        .len = 60,
        .crc32 = 0x11d056c3,
    };
    
    testcase test2 = {
        .buffer = (uint8_t*)&_binary___test2_bin_start,
        .len = 60,
        .crc32 = 0xbb327374,
    };
   
    testcase test3 = {
        .buffer = (uint8_t*)&_binary___test3_bin_start,
        .len = 60,
        .crc32 = 0x3e869219,
    };
    
    testcase test4 = {
        .buffer = (uint8_t*)&_binary___test4_bin_start,
        .len = 74,
        .crc32 = 0xe313cb8b,
    };

    testcase test5 = {
        .buffer = (uint8_t*)&_binary___test5_bin_start,
        .len = 68,
        .crc32 = 0x7d84c61c,
    };

    /* Tests for slow CRC algorithm */
    test_crc32_slow_returns_correct_value_for_ethernet(&test1);
    test_crc32_slow_returns_correct_value_for_ethernet(&test2);
    test_crc32_slow_returns_correct_value_for_ethernet(&test3);
    test_crc32_slow_returns_correct_value_for_ethernet(&test4);
    test_crc32_slow_returns_correct_value_for_ethernet(&test5);
    test_crc32_slow_input_reversal();
    test_crc32_slow_output_reversal();
    test_crc32_slow_output_inversion();

    /* Tests for fast CRC algorithm */
    test_crc32_fast_returns_correct_value_for_ethernet(&test1);
    test_crc32_fast_returns_correct_value_for_ethernet(&test2);
    test_crc32_fast_returns_correct_value_for_ethernet(&test3);
    test_crc32_fast_returns_correct_value_for_ethernet(&test4);
    test_crc32_slow_returns_correct_value_for_ethernet(&test5);
    test_crc32_fast_input_reversal();
    test_crc32_fast_output_reversal(); 
    test_crc32_fast_output_inversion();

    /* Performance tests */
    test_crc32_performance();

    return 0;
}
