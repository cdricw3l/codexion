/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/22 11:38:43 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


void *threading(void *data)
{
    pthread_mutex_t *mu;

    printf("je suis le thread  %ld\n", pthread_self());
    mu = (pthread_mutex_t *)data;
    pthread_mutex_lock(mu);
    printf("%ld a locker le mutex\n", pthread_self());
    sleep(2);
    pthread_mutex_unlock(mu);
    printf("%ld a unlocker le mutex\n", pthread_self());
    return (NULL);    
}

// int main(void)
// {
//     pthread_mutex_t mutex;
//     pthread_t thread[5];

//     for (int i = 0; i < 5; i++)
//     {
//         pthread_create(&thread[i], NULL, threading, &mutex);
//         usleep(100000);
//     }

//     sleep(1);
    
//     for (int j = 0; j < 5; j++)
//         pthread_join(thread[j], NULL);
    
// }


int main(void)
{
    pthread_mutex_t mu;

    printf("first_lock %d\n", pthread_mutex_lock(&mu));
    printf("second_lock %d\n", pthread_mutex_unlock(&mu));
}
