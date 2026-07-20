/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:07:31 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 19:43:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

struct timespec time_diff(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec + - start.tv_sec - 1;
        temp.tv_nsec =  1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

clock_t time_calculation(struct timespec time)
{
    /* convert second to nano*/
    clock_t n_to_sec;

    n_to_sec  = time.tv_sec * 1000000000;
    return ((n_to_sec + time.tv_nsec) / 1000000);
}