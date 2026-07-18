/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/18 09:03:26 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void set_timestamp(int *dashboard)
{
    struct timespec time;

    clock_gettime(CLOCK_REALTIME, &time);
    *dashboard = time.tv_nsec;
}

void update_timestamps(int *dashboard)
{
    pthread_mutex_t mu;
    pthread_mutex_lock(&mu);
    set_timestamp(dashboard);
    pthread_mutex_unlock(&mu);

}

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
    return (c >= 48 && c <= 57);
}

void ft_memcopy(void *src, void *dst, unsigned long size)
{
    unsigned long i;

    i = 0;
    while (i < size)
    {
        ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
        i++;
    }
}
int get_dongle(int id, int number_of_coder, int type)
{
    if (type == RIGHT)
        return (id);
    if (type == LEFT)
    {
        if (id == 0)
            return (number_of_coder - 1);
        else
            return (id - 1);
    }
    return (-1);
}