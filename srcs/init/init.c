/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:22:43 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/28 01:25:56 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int clean_simulation(t_simulation *sim, int code)
{
    pthread_mutex_destroy(&sim->sim_state_mutex);
    pthread_mutex_destroy(&sim->display_mutex);
    if(sim->dongles)
        clean_dongles(sim->dongles, sim->params[number_of_coders]);
    if(sim->timestamp)
        free(sim->timestamp);
    if (sim->timestamp_mutext)
        clean_dynamique_mutex(sim->timestamp_mutext, sim->params[number_of_coders]);
    return (code);
    
}

int init_simulation(int params[8], t_simulation *sim)
{
    ft_memcopy(params, sim->params, 8 * sizeof(int));
    sim->simulation_state = OFF;
    if (pthread_mutex_init(&sim->sim_state_mutex, NULL))
        return (FALSE);
    if (pthread_mutex_init(&sim->display_mutex, NULL))
    {
        pthread_mutex_destroy(&sim->sim_state_mutex);
        return (FALSE);
    }
    sim->dongles = dongles_initialisation(params[number_of_coders]);
    if (!sim->dongles)
    {
        write(STDERR_FILENO, "Error initialisation dongle\n", strlen("Error initialisation dongle\n"));
        return(clean_simulation(sim, FALSE));
    }
    sim->timestamp = init_dyn_arr(params[number_of_coders], sizeof(clock_t));
    if (!sim->timestamp)
        return (clean_simulation(sim, FALSE));
    sim->timestamp_mutext = init_mutex(params[number_of_coders]);
    if (!sim->timestamp_mutext)
        return (clean_simulation(sim, FALSE));
    return (TRUE);
}
