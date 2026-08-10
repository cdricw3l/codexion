/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:27:10 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 13:11:07 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

#define DISPLAY_PARAM FALSE
#define DISPLAY_DONGLES FALSE

pthread_t *init_coder_thread(int nb)
{
    pthread_t   *thrd_coder;

    thrd_coder = malloc(sizeof(pthread_t) * nb);
    if(!thrd_coder)
        return (NULL);
    return (thrd_coder);
}

clock_t *init_timestamps(int nb)
{
    clock_t *timestamps;

    timestamps = malloc(sizeof(clock_t) * nb);
    if (!timestamps)
        return (NULL);
    memset(timestamps, 0, sizeof(clock_t) * nb);
    return(timestamps);
}
pthread_mutex_t *init_mutex(int nb)
{
    pthread_mutex_t *mu;
    int             i;
    int             j;
    
    mu = malloc(sizeof(pthread_mutex_t) * nb);
    if (!mu)
        return (NULL);
    i = 0;
    while (i < nb)
    {
        if (pthread_mutex_init(&mu[i], NULL))
        {
            j = 0;
            while (j < i)
                pthread_mutex_destroy(&mu[j++]);
            free(mu);
            return (NULL);            
        }
        i++;
    }
    return (mu);
}

pthread_cond_t *init_cond(int nb)
{
    pthread_cond_t *cond;
    int             i;
    int             j;
    
    cond = malloc(sizeof(pthread_cond_t) * nb);
    if (!cond)
        return (NULL);
    i = 0;
    while (i < nb)
    {
        if (pthread_cond_init(&cond[i], NULL))
        {
            j = 0;
            while (j < i)
                pthread_cond_destroy(&cond[j++]);
            free(cond);
            return (NULL);            
        }
        i++;
    }
    return (cond);
}

int init_sim(int *params, t_dongle *dongles, t_sim *sim)
{
    sim->params = params;
    sim->coders = init_coder_thread(params[number_of_coders]);
    if (!sim->coders)
        return (msg_error(CODER));
    sim->dongles = dongles;
    sim->timestamp = init_timestamps(params[number_of_coders]);
    if (!sim->timestamp)
    {
        free(sim->coders);
        return (msg_error(TIMESTAMPS));
    }
    sim->timestamp_mu = init_mutex(params[number_of_coders]);
    if (!sim->timestamp_mu)
    {
        free(sim->coders);
        free(sim->timestamp);
        return (msg_error(TIMESTAMPS_MUTEX));
    }
    sim->display_mu = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    sim->coder_mu = init_mutex(params[number_of_coders]);
    if (!sim->coder_mu)
    {
        free(sim->coders);
        free(sim->timestamp);
        free(sim->timestamp_mu);
        return (msg_error(CODER_MUTEX));
    }
    sim->coder_cond = init_cond(params[number_of_coders]);
    if(!sim->coder_cond)
    {
        free(sim->coders);
        free(sim->timestamp);
        free(sim->timestamp_mu);
        free(sim->coder_mu);
        return (msg_error(CODER_COND));
    }
    return (0);
}


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
    t_sim       sim;
    int         params[8];
    
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
    printf(HGRN"INITIALISATION [OK]"CRESET"\n");
    clean_sim(&sim);
    clean_dongles(dongles, params[number_of_coders]);
    return (0);
}