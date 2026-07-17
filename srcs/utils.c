/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 14:28:08 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

size_t get_str_arr_len(char **str_arr)
{
    size_t size;

    if(!str_arr)
        return (0);
    size = 0;
    while (*str_arr)
    {
        str_arr++;
        size++;
    }
    return (size);
}

int ft_is_digit(char c)
{
    return c >= 48 && c <= 57;
}

void ft_memcopy(void *src, void *dst, unsigned long size)
{
    unsigned long i;

    i = 0;
    while (i < size)
    {
        DEBUG;
        printf("%d\n", i);
        ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
        i++;
    }
}