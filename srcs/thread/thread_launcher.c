/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_launcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 19:54:35 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/11 12:29:59 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"


int launch_thread(t_data *data, t_sim *sim)
{
    
    (void)data;
    sim->simulation_state = ON;
    pthread_create(&sim->scheduler, NULL, scheduler_routine, sim);
    pthread_create(&sim->monitor, NULL, monitor_routine, sim);
    pthread_join(sim->monitor, NULL);
    pthread_mutex_lock(&sim->display_mu);
    printf("Monitor is joined\n");
    pthread_mutex_unlock(&sim->display_mu);
    pthread_join(sim->scheduler, NULL);
    pthread_mutex_lock(&sim->display_mu);
    printf("Scheduler is joined\n");
    pthread_mutex_unlock(&sim->display_mu);
    
    
    return (TRUE);
}