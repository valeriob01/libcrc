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
