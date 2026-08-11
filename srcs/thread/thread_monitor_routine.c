/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_routine.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:33:42 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/11 12:32:10 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"


void *monitor_routine(void *data)
{
    t_sim *sim;
    int i;

    sim = (t_sim *)data;
    i = get_param(sim, number_of_compiles_required);
    while (i >= 0)
    {
        pthread_mutex_lock(&sim->display_mu);

        printf("I`m the monitor %d\n", i);
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
        i--;
    }
    pthread_mutex_lock(&sim->simulation_mu);
    sim->simulation_state = OFF;
    pthread_mutex_unlock(&sim->simulation_mu);
    return (NULL);
}
