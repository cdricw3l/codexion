/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:17:45 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 15:47:20 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"


void *scheduler_routine(void *data)
{
    int i;
    t_scheduler *scheduler;

    scheduler = (t_scheduler *)data;
    assert(scheduler->nb_coder == 4);
    while (1)
    {
        i = 0;
        while (i < scheduler->nb_coder)
        {
            pthread_mutex_lock(&scheduler->can_compile_mu[i]);
            sleep(1);    
            pthread_mutex_unlock(&scheduler->can_compile_mu[i]);
            pthread_cond_signal(&scheduler->can_compile_co[i]);
            i++;
        }
    }
    return (NULL);
}