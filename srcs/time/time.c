/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:07:31 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/04 21:29:44 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

long second_to_nano(long sec)
{
    return (sec * 1000000000);
}

long ms_to_nano(long ms)
{
    return (ms * 1000000);
}

long nano_to_ms(long nano)
{
    return (nano / 1000000);
}
struct timespec futuristic_timespec(int ms)
{
    struct timespec now;
    struct timespec futuristic;
    
    clock_gettime(CLOCK_REALTIME, &now);
    if(now.tv_nsec + ms_to_nano(ms) > 999999999)
    {

        futuristic.tv_nsec = ms_to_nano(ms) - (999999999 - now.tv_nsec);
        futuristic.tv_sec = now.tv_sec + 1;
    }
    else
    {
        futuristic.tv_sec = now.tv_sec;
        futuristic.tv_nsec = now.tv_nsec + ms_to_nano(ms);
    }
    return (futuristic);
}

struct timespec time_diff(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec  - start.tv_sec - 1;
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



void set_timestamp(t_coder *coder, int type)
{
    
    timespec_t now;

    clock_gettime(CLOCK_MONOTONIC, &now);
    if(type == TIMESTAMP_COMPILATION)
    {
        pthread_mutex_lock(coder->coder_mutex.timestamp_f);
        *(coder->last_compilation) = now.tv_nsec + second_to_nano(now.tv_sec);
        coder->nb_of_compil++;
        pthread_mutex_unlock(coder->coder_mutex.timestamp_f);
    }    
    else if(type == TIMESTAMP_DONGLE)
    {   
        coder->coder_mutex.dongle_l.last_use = now.tv_nsec + second_to_nano(now.tv_sec);
        coder->coder_mutex.dongle_r.last_use = now.tv_nsec + second_to_nano(now.tv_sec);
    }
}