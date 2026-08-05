/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:17:45 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 17:21:51 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"


void *scheduler_routine(void *data)
{
    int i;
    t_scheduler *scheduler;

    scheduler = (t_scheduler *)data;
    while (1)
    {
        i = 0;
        while (i < scheduler->nb_coder)
        {
            pthread_mutex_lock(&scheduler->can_compile_mu[i]);
            pthread_mutex_lock(&scheduler->queue->queue_lock);
            if(*scheduler->queue->request_queue && scheduler->queue->request_queue[0]->coder_id)
            {
                scheduler->can_compile[i] = TRUE;
                pop_request(scheduler->queue);
            }
            pthread_mutex_unlock(&scheduler->queue->queue_lock);
            pthread_mutex_unlock(&scheduler->can_compile_mu[i]);
            pthread_cond_signal(&scheduler->can_compile_co[i]);
            usleep(5000);
            i++;
        }
    }
    return (NULL);
}