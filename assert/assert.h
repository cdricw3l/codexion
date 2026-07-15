#ifndef ASSERT_H
#define ASSERT_H

#include "../include/codexion.h"
#include "./color-codes.h"

#define START_TEST(name) printf(HYEL"Start test module: %s\n"CRESET, name)
#define END_TEST(name) printf(HGRN"test module: %s [OK]\n"CRESET, name)

void get_str_arr_len_assert(void);


#endif