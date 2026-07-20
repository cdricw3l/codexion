/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 07:43:06 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


void *coder_thread(void *data)
{
    t_coder *coder;
    
    coder = (t_coder *)data;
    while (coder->params.ncr > 0)
    {
        pthread_mutex_lock(coder->dongle_l);
        pthread_mutex_lock(coder->dongle_r);
        //update_timestamps(coder->last_compile);
        safe_print(*coder, TAKE);
        safe_print(*coder, COMPILE);
        /* compiling */
        usleep(coder->params.ttc * 1000);
        /* cooldown */
        usleep(coder->params.dc * 1000);
        pthread_mutex_unlock(coder->dongle_l);
        pthread_mutex_unlock(coder->dongle_r);
        /* debbuging */
        safe_print(*coder, DEBBUG);
        usleep(coder->params.ttd * 1000);
        safe_print(*coder, REFACTO);
        usleep(coder->params.ttr * 1000);
        coder->params.ncr--;
    }
    return (NULL);
}

void *monitoring_thread(void *data)
{
    t_monitoring *monitor;
    struct timespec now;
    time_t ref;
    int i;

    monitor = (t_monitoring *)data;
    while (1)
    {   
        printf("nombre de coder %d\n", monitor->nb_coder);
        i = 0;
        while (i < monitor->nb_coder)
        {
            
            // pthread_mutex_lock(&monitor->dashboard_mu[i]);
            // ref = monitor->dashboard[i];
            // pthread_mutex_unlock(&monitor->dashboard_mu[i]);
            // clock_gettime(0, &now);
            // if (now.tv_nsec - ref > (monitor->ttb * 1000000))
            //     printf("Philo %d is dead\n", i);
            i++;
            usleep(10000);
        }
    }
    return (NULL);
}

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
    /* CODER_MAX is the num of thread max  -1 for the monitoring thread les see to reduce de max philo to 200 (evalsheet max)*/
    pthread_t       thread_coders[2000];
    pthread_t       thread_monitoring;
    t_coder         **coders;
    time_t          *dashboard;
    struct          timeval start;

    dashboard = malloc(sizeof(time_t) * param->coder);
    if(!dashboard)
        return (FALSE);
    memset(dashboard, 0, sizeof(time_t) * param->coder);
    coders = init_coder(param, dongles, dashboard_mu, dashboard);
    if(!coders)
    {
        free(dashboard);
        return (FALSE);
    }
    if(!launch_monitoring_thread(dashboard, dashboard_mu, *param, &thread_monitoring))
    {
        free(dashboard);
        destroy_coders(&coders, param->coder);
        return (FALSE);
    }
    i = 0;

    gettimeofday(&start, NULL);
    while (i < param->coder)
    {
        coders[i]->start = start.tv_usec;
        pthread_create(&thread_coders[i], NULL, coder_thread, coders[i]);
        usleep(100000);
        i++;
    }
    i = 0;
    while(i < param->coder)
    {
        pthread_join(thread_coders[i], NULL);
        free(coders[i]);
        i++;
    }
    pthread_join(thread_monitoring, NULL);
    free(coders[i]);
    free(coders);
    return (TRUE);
}
