/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_launcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 19:54:35 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 20:11:05 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void *scheduler_routine(void *data)
{
    t_sim *sim;

    sim = (t_sim *)data;
    while (1)
    {
        pthread_mutex_lock(&sim->display_mu);

        printf("I`m the scheduler");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);
        printf("\n");
        pthread_mutex_unlock(&sim->display_mu);

    }
    
}

int launch_thread(t_data *data, t_sim *sim)
{
    //int nb_coder;
    //int i;

    //i = 0;
    //nb_coder = sim->params[number_of_coders];
    (void)data;
    pthread_create(&sim->scheduler, NULL, scheduler_routine, sim);
    pthread_join(sim->scheduler, NULL);
    
    return (TRUE);
}