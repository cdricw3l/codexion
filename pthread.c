/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/23 08:15:11 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

typedef struct s_data
{

    int                 *stock;
    pthread_mutex_t     *mu;
    pthread_cond_t      *cond;

} t_data;

long second_to_nano(long sec)
{
    return (sec * 1000000000);
}

long ms_to_nano(long ms)
{
    return (ms * 1000000);
}

void display_time(struct timespec tm)
{
    printf("sec: %ld\n", tm.tv_sec);
    printf("nsec: %ld\n", tm.tv_nsec);
    printf("\n");
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

void cooldown(int ms, pthread_cond_t *cond, pthread_mutex_t *mu)
{
    struct timespec tm;
    
    int rt = 0;

    struct timespec now;

    clock_gettime(CLOCK_REALTIME, &now);
    if(now.tv_nsec + ms > 999999999)
    {
        tm.tv_nsec = 999999999 - ms;
        tm.tv_sec = now.tv_sec + 1;
    }
    else
    {
        printf("Case 2");
        tm.tv_sec = now.tv_sec;
        tm.tv_nsec = now.tv_nsec + ms;
    }
    do  {
        rt = pthread_cond_timedwait(cond, mu, &tm);
    }
    while (rt == 0);

}


void *consume(void *d)
{
    t_data *data;

    data = (t_data *)d;
    while (1)
    {
        pthread_mutex_lock(data->mu);
        pthread_mutex_unlock(data->mu);
    }
    return (NULL);
}





// int main(void)
// {
//     int stock;
//     pthread_mutex_t mu;
//     pthread_cond_t  cond;
//     t_data          data;
//     pthread_t       thread;

//     mu = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
//     cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
//     stock = 0;
//     pthread_create(&thread, NULL, consume, &data);

//     pthread_join(thread, NULL);

// }

int main(void)
{

    struct timespec now;
    struct timespec future;


    
    clock_gettime(CLOCK_REALTIME, &now);
    future = futuristic_timespec(200);

    printf("voici la difference %ld\n", time_calculation(time_diff(now, future)));

    return (0);
}

