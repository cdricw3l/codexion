/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_scheduler_routine.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:33:42 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/11 12:28:39 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void *scheduler_routine(void *data)
{
    t_sim *sim;

    sim = (t_sim *)data;
    while (check_simulation_state(sim))
    {
        pthread_mutex_lock(&sim->display_mu);

        printf("I`m the scheduler");
        fflush(stdout);
        usleep(100000);
        printf(".");
        fflush(stdout);
        usleep(100000);
        printf(".");
        fflush(stdout);
        usleep(100000);
        printf(".");
        fflush(stdout);
        usleep(100000);
        printf("\n");
        pthread_mutex_unlock(&sim->display_mu);
        usleep(100000);
    }
    return (NULL);
}
