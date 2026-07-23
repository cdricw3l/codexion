/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/22 17:08:18 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/codexion.h"

long second_to_nano(long sec)
{
    return (sec * 1000000000);
}

long ms_to_nano(long ms)
{
    return (ms * 1000000);
}

void display_clock(struct timespec tm)
{
    printf("second: %ld\n", tm.tv_sec);
    printf("nano second: %ld\n", tm.tv_nsec);
}

int schedul(struct timespec *tm, int ms)
{
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
    if(now.tv_nsec + ms_to_nano(ms) > 999999999)
    {
        tm->tv_nsec = 999999999 - ms_to_nano(ms);
        tm->tv_sec = now.tv_sec + 1;
    }
    else
    {
        tm->tv_sec = now.tv_sec;
        tm->tv_nsec = now.tv_nsec + ms_to_nano(ms);
    }
}



void cool_test(pthread_cond_t *cond, pthread_mutex_t *mu)
{
    int rt = 0;
    struct timespec tm;

    schedul(&tm, 500);
    pthread_mutex_lock(mu);
    do  {
        rt = pthread_cond_timedwait(cond, mu, &tm);
        printf("voici rt %d\n", rt);
    }
    while (rt == 0);
    pthread_mutex_unlock(mu);
}

int main(void)
{
    
    struct timespec tm1;
    struct timespec tm2;
    struct timespec start;
    struct timespec end;

    pthread_mutex_t cool;
    pthread_cond_t  cool_cond;

    cool = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    cool_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    
   
    
   
    clock_gettime(CLOCK_REALTIME, &start);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("start\n");
    display_clock(start);
    printf("end\n");
    display_clock(end);

    return (0);
}