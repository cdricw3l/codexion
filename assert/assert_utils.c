/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/15 14:26:27 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void get_str_arr_len_assert(void)
{
    char *arr0[] = {"hello", "berlin", "how are you", NULL};
    char *arr1[] = {"hello", "berlin", NULL};
    char *arr2[] = { NULL};
    assert(get_str_arr_len(arr0) == 3);
    assert(get_str_arr_len(arr1) == 2);
    assert(get_str_arr_len(arr2) == 0);
    assert(get_str_arr_len(NULL) == 0);

}