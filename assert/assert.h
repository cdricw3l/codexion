#ifndef ASSERT_H
#define ASSERT_H

#include "../include/codexion.h"
#include "../include/color-codes.h"

#define START_TEST(name) printf(HYEL"Start test module: %s\n"CRESET, name)
#define END_TEST(name) printf(HGRN"test module: %s [OK]\n"CRESET, name)

int create_request_assert(void);
int remove_request_assert(void);
void poppush_queue_assert(void);
int bfs_binary_tree_as_arr_assert(void);

#endif