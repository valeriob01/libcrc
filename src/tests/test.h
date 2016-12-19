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

#ifndef __TEST_H__
#define __TEST_H__

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN  " \x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE  "\x1b[34m"

#define FAIL() printf(ANSI_COLOR_RED" FAILED "ANSI_COLOR_RED" %s (line %d)\n", __func__, __LINE__)
#define PASSED() printf(ANSI_COLOR_GREEN "PASSED "ANSI_COLOR_BLUE" %s \n", __func__)
#define RESULT(res) printf(ANSI_COLOR_GREEN "PASSED "ANSI_COLOR_BLUE" %s:" ANSI_COLOR_RESET" %s \n", __func__, res)

#define _assert(test) do { if (!(test)) { FAIL(); } else PASSED(); } while(0)

#endif
