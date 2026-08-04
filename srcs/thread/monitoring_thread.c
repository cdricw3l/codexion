/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:08:49 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/04 12:48:26 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int check_timestamp(t_coder *coder ,clock_t last_c, int *params)
{
    timespec_t  now;
    clock_t     now_in_nano;
    int         diff;

    clock_gettime(CLOCK_MONOTONIC, &now);
    now_in_nano = (now.tv_nsec + second_to_nano(now.tv_sec));
    diff = nano_to_ms(now_in_nano - last_c);

    if(diff > params[time_to_burnout] && coder->nb_of_compil > 0 && coder->nb_of_compil < params[number_of_compiles_required])
    {
        //printf("coder %d: last compilation: %ld now: %ld diff in nano: %ld diff in ms %ld \n", coder->id, last_c, now_in_nano, now_in_nano - last_c, nano_to_ms(now_in_nano - last_c));
        return (FALSE);
    }
    return (TRUE);
}

int check_end(t_coder *coder)
{
    int i;
    int check;
    int compilation_nedeed;
    int nb_coder;

    i = 0;
    check = 0;
    compilation_nedeed = coder[0].params[number_of_compiles_required];
    nb_coder = coder[0].params[number_of_coders];
    while (i < nb_coder)
    {
        if(coder[i].nb_of_compil == compilation_nedeed)
            check++;
        i++;
    }
    if(check == nb_coder)
        return (TRUE);
    return (FALSE);
}

void *monitor_routine(void *data)
{
    int i;
    t_monitoring *monitor;
    
    monitor = (t_monitoring *)data;
    i = 0;
    
    while (1)
    {
        i = 0;
        pthread_mutex_lock(monitor->timestamp_f);
        while (i < monitor->nb_coder)
        {
            if(!check_timestamp(&monitor->coder[i], monitor->last_compilations[i], monitor->params))
            {
                safe_print(monitor->coder[i], DEAD, monitor->display_f);
                int j = 0;
                while (j < monitor->nb_coder)
                {
                    pthread_mutex_lock(&monitor->state[j]);
                    monitor->coder[j].state = FALSE;
                    pthread_mutex_unlock(&monitor->state[j]);
                    j++;
                }
                return (NULL);

            }
            i++;
            pthread_mutex_unlock(monitor->display_f);
        }
        pthread_mutex_unlock(monitor->timestamp_f);
        usleep(200000);

        if (check_end(monitor->coder))
            break;
    }
    return (NULL);
}