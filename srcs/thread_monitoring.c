/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 20:15:32 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 20:17:16 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *monitoring_thread(void *data)
{
    t_monitoring *monitor;
    struct timespec now;
    time_t ref;
    int i;

    monitor = (t_monitoring *)data;
    while (1)
    {   
        printf("nombre de coder %d\n", monitor->nb_coder);
        i = 0;
        while (i < monitor->nb_coder)
        {
            
            // pthread_mutex_lock(&monitor->dashboard_mu[i]);
            // ref = monitor->dashboard[i];
            // pthread_mutex_unlock(&monitor->dashboard_mu[i]);
            // clock_gettime(0, &now);
            // if (now.tv_nsec - ref > (monitor->ttb * 1000000))
            //     printf("Philo %d is dead\n", i);
            i++;
            usleep(10000);
        }
    }
    return (NULL);
}