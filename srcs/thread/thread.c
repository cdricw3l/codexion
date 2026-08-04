/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:09:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/04 13:10:01 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"


int thread_launcher(t_coder *coders,t_monitoring *monitor, int nb_coder)
{
    int         i;
    pthread_t   *thread_coder;
    pthread_t   thread_monitor;
    timespec_t  now;

    thread_coder = malloc(sizeof(pthread_t) * nb_coder);
    assert(thread_coder);
    i = 0;
    clock_gettime(CLOCK_MONOTONIC, &now);
    while (i < nb_coder)
    {
        coders[i].last_compilation  = &monitor->last_compilations[i];
        assert(*(coders[i].last_compilation) == -1);
        coders[i].start = now;
        coders[i].state = TRUE;
        pthread_create(&thread_coder[i], NULL, coder_routine, &coders[i]);
        usleep(50000);
        i++;
    }
    pthread_create(&thread_monitor, NULL, monitor_routine, monitor);
    pthread_join(thread_monitor, NULL);
    i = 0;
    while (i < nb_coder)
    {
        if(pthread_join(thread_coder[i], NULL))
            printf("Error join\n");
        //assert(coders[i].nb_of_compil == coders->params[number_of_compiles_required]);
        i++;
    }
    
    free(thread_coder);
    return (TRUE);
    
}