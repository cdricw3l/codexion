/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 20:20:42 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


int launch_monitoring_thread(time_t *dashboard, mutex_t *dashboard_mu, t_params params, pthread_t *monitoring)
{
    t_monitoring    monitoring_data;

    monitoring_data.dashboard = dashboard;
    monitoring_data.dashboard_mu = dashboard_mu;
    monitoring_data.nb_coder = params.coder;
    monitoring_data.ttb = params.ttb;
    assert(monitoring_data.nb_coder == 2);
    display_monitoring_dashboard(dashboard, monitoring_data.nb_coder);
    if(pthread_create(monitoring, NULL, monitoring_thread, &monitoring_data) != 0)
    {
        perror("thread monitoring creation error");
        return(FALSE);
    }
    printf("Thread de monitoring initialisé\n");
    return (TRUE);
}

int thead_luncher(t_params *param, mutex_t *dongles, mutex_t *dashboard_mu)
{

    size_t          i;
    pthread_mutex_t mu_print;
    /* CODER_MAX is the num of thread max  -1 for the monitoring thread les see to reduce de max philo to 200 (evalsheet max)*/
    pthread_t       thread_coders[2000];
    pthread_t       thread_monitoring;
    t_coder         **coders;
    clock_t          *dashboard;
    struct          timespec start;

    dashboard = malloc(sizeof(clock_t) * param->coder);
    if(!dashboard)
        return (FALSE);
    memset(dashboard, 0, sizeof(clock_t) * param->coder);
    coders = init_coder(param, dongles, dashboard_mu, dashboard);
    if(!coders)
    {
        free(dashboard);
        return (FALSE);
    }
    // if(!launch_monitoring_thread(dashboard, dashboard_mu, *param, &thread_monitoring))
    // {
    //     free(dashboard);
    //     destroy_coders(&coders, param->coder);
    //     return (FALSE);
    // }
    pthread_mutex_init(&mu_print, NULL);
    i = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (i < param->coder)
    {
        coders[i]->start = start;
        coders[i]->mu_print = &mu_print;
        pthread_create(&thread_coders[i], NULL, coder_thread, coders[i]);
        usleep(100);
        i++;
    }
    i = 0;
    while(i < param->coder)
    {
        pthread_join(thread_coders[i], NULL);
        free(coders[i]);
        i++;
    }
    pthread_mutex_destroy(&mu_print);
    //pthread_join(thread_monitoring, NULL);
    free(coders[i]);
    free(coders);
    free(dashboard);
    return (TRUE);
}
