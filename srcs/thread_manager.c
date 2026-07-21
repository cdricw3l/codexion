/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/21 09:21:39 by cebouhad         ###   ########.fr       */
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
    if (pthread_create(monitoring_data, NULL, monitoring_thread, monitoring_data))
        return (FALSE);
    return (TRUE);
}

int thead_launcher(t_params *params, t_coder *coders, t_monitoring *monitoring)
{
    pthread_t monitoring_t;


    display_coders(coders, params->coder);


    
    return (TRUE);
}
