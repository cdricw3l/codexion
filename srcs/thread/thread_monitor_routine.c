/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_routine.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:33:42 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/11 16:09:52 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void *routine_coder(void *d)
{
    t_data *data;

    data = (t_data *)d;
    while (check_simulation_state(data->sim, ON))
    {
        pthread_mutex_lock(&data->sim->display_mu);
        printf("im the coder: %d\n", data->id);
        pthread_mutex_unlock(&data->sim->display_mu);
    }
    return (NULL);
}

int launch_coder(t_data *data, int nb_coder, int *are_launched)
{
    int i;
    timespec_t now;

    i = 0;
    clock_gettime(CLOCK_MONOTONIC, &now);
    while (i  < nb_coder)
    {
        data->sim->start = now.tv_nsec + (now.tv_sec * 1000000);
        pthread_create(&data->sim->coders[i], NULL, routine_coder, data);
        i++;
    }
    *(are_launched) = TRUE;
    return (TRUE);
}

int join_coder(t_data *data, int nb_coder)
{
    int i;

    i = 0;
    while (i < nb_coder)
    {
        pthread_join(data->sim->coders[i], NULL);
        i++;
    }
    printf("All coder are joined\n");
    return (TRUE);
}


void *monitor_routine(void *d)
{
    t_data *data;
    int nb;
    int are_launched;

    data = (t_data *)d;
    nb = get_param(data->sim, number_of_compiles_required);
    are_launched = FALSE;
    printf("Monitor Launch coder\n");
    while (nb >= 0)
    {
        if(are_launched == 0)
            launch_coder(data, nb, &are_launched);
        pthread_mutex_lock(&data->sim->display_mu);
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
        pthread_mutex_unlock(&data->sim->display_mu);
        usleep(100000);
        nb--;
    }
    pthread_mutex_lock(&data->sim->simulation_mu);
    data->sim->simulation_state = OFF;
    pthread_mutex_unlock(&data->sim->simulation_mu);
    join_coder(data, nb);
    return (NULL);
}
