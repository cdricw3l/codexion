/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 20:15:32 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/21 09:38:06 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *monitoring_thread(void *data)
{
    t_monitoring *monitor;
    size_t i;

    monitor = (t_monitoring *)data;
    printf("nombre de coder %d\n", monitor->nb_coder);

    while (1)
    {   
        i = 0;
        while (i < monitor->nb_coder)
        {   
            pthread_mutex_lock(&monitor->m_timestamp_data[i]);
            printf("coder [%ld] last compilation %ld\n", i, monitor->timestamps_arr[i]);
            pthread_mutex_unlock(&monitor->m_timestamp_data[i]);
            usleep(800000);
            i++;
        }
    }
    return (NULL);
}