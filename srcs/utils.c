/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 11:21:29 by cebouhad         ###   ########.fr       */
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

void copy_coder(t_coder *c1, t_coder *c2)
{
    unsigned long i;

    i = 0;
    while (i < sizeof(*c1))
    {
        ((unsigned char *)c2)[i] = ((unsigned char * )c1)[i];
        i++;
    }
}