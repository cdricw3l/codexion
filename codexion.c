/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:27:10 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 20:07:41 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

#define CHECK_SIMULATION TRUE
#define DISPLAY_PARAM FALSE
#define DISPLAY_DONGLES FALSE






int clean_sim(t_sim *sim)
{
    int i;
    int nb;

    i = 0;
    nb = sim->params[number_of_coders];
    while (i < nb)
    {
        pthread_cond_destroy(&sim->coder_cond[i]);
        pthread_mutex_destroy(&sim->timestamp_mu[i]);
        pthread_mutex_destroy(&sim->coder_mu[i]);
        i++;
    }
    pthread_mutex_destroy(&sim->display_mu);
    free(sim->coders);
    free(sim->timestamp);
    free(sim->coder_cond);
    free(sim->coder_mu);
    free(sim->timestamp_mu);
    free(sim->timestamp);
    return (TRUE);
    
}

int main(int argc, char **argv)
{
    t_dongle    *dongles;
    t_data      data[CODER_MAX];
    t_sim       sim;
    int         params[PARAMS_SIZE];
    
    if(!parse_arguments(&argv[1], params))
        return (write(STDERR_FILENO, "Error parsinfg arguments\n", strlen("Error parsinfg arguments\n")));
    if (DISPLAY_PARAM)
        display_params(params, argc - 1);
    dongles = dongles_initialisation(params[number_of_coders]);
    if(!dongles)
    {
        write(STDERR_FILENO, "Error initialisation dongle\n", strlen("Error initialisation dongle\n"));
        return(1);
    }
    if (DISPLAY_DONGLES)
        display_dongles_data(dongles, params[number_of_coders]);
    if (init_sim(params, dongles, &sim))
    {
        write(STDERR_FILENO, "Error initialisation simulation\n", strlen("Error initialisation simulation\n"));
        clean_dongles(dongles, params[number_of_coders]);
        return(1);
    }
    if (CHECK_SIMULATION)
        check_simulation_data(&sim);

    launch_thread(data, &sim);

    
    clean_sim(&sim);
    clean_dongles(dongles, params[number_of_coders]);
    
    return (0);
}