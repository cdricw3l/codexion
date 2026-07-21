/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/21 10:13:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


// int launch_monitoring_thread(time_t *dashboard, mutex_t *dashboard_mu, t_params params, pthread_t *monitoring)
// {
//     t_monitoring    monitoring_data;

//     monitoring_data.dashboard = dashboard;
//     monitoring_data.dashboard_mu = dashboard_mu;
//     monitoring_data.nb_coder = params.coder;
//     monitoring_data.ttb = params.ttb;
//     assert(monitoring_data.nb_coder == 2);
//     display_monitoring_dashboard(dashboard, monitoring_data.nb_coder);
//     if(pthread_create(monitoring, NULL, monitoring_thread, &monitoring_data) != 0)
//     {
//         perror("thread monitoring creation error");
//         return(FALSE);
//     }
//     printf("Thread de monitoring initialisé\n");
//     return (TRUE);
// }

static int launcher_monitoring(pthread_t *monitoring_t, t_monitoring *monitoring_data)   
{
    printf("Start\n");
    if (pthread_create(monitoring_t, NULL, monitoring_thread, monitoring_data))
    {
        perror("Monitoring Thread launcher: ");
        return (FALSE);
    }
    return (TRUE);
}

static int launcher_coders(size_t nb_coders, pthread_t *coders_t, t_coder *coders)   
{
    size_t i;
    struct timespec tm;
    i = 0;

    clock_gettime(CLOCK_MONOTONIC, &tm);
    while (i < nb_coders)
    {
        coders[i].start = tm;
        if (pthread_create(&coders_t[i], NULL, coder_thread, &coders[i]))
        {
            perror("Monitoring Thread launcher: ");
            return (FALSE);
        }
        usleep(1000);
        i++;
    }
    
    return (TRUE);
}

int thead_launcher(size_t nb_coders, t_coder *coders, t_monitoring *monitoring)
{
    pthread_t   monitoring_t;
    pthread_t   *coders_t;
    size_t      i;

    coders_t = malloc(sizeof(pthread_t) * nb_coders);
    if (!coders)
    {
        write(STDERR_FILENO, "Coder thread allocation error\n", strlen("Coder thread allocation error\n"));
        return (FALSE);
    }
    //launcher_monitoring(&monitoring_t, monitoring);
    launcher_coders(nb_coders, coders_t, coders);
    //pthread_join(monitoring_t, NULL);
    i = 0;
    while (i < nb_coders)
        pthread_join(coders_t[i++], NULL);
    free(coders_t);
    return (TRUE);
}
