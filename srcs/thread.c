/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/18 22:48:49 by cebouhad         ###   ########.fr       */
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
        i = 0;
        while (i < monitor->nb_coder)
        {
            pthread_mutex_lock(&monitor->dashboard_mu[i]);
            ref = monitor->dashboard[i];
            pthread_mutex_unlock(&monitor->dashboard_mu[i]);
            clock_gettime(0, &now);
            if (now.tv_nsec - ref > (monitor->ttb * 1000000))
                printf("Philo %d is dead\n", i);
            i++;
            usleep(10000);
        }
    }
    return (NULL);
}

void *destroy_coders(t_coder ***coders, int idx)
{
    t_coder **c;
    int i;

    c = *coders;
    i = 0;
    while (i <= idx)
        free(c[i++]);
    free(*coders);
    return (NULL);
}

t_coder **init_coder(t_params *params, mutex_t *dongles, mutex_t *dashboard_mu, int *dashboard)
{
    size_t  i;
    t_coder **coders;
    t_coder *coder;
    i = 0;
    coders = malloc(sizeof(t_coder *) * (params->coder + 1));
    if (!coders)
        return (NULL);
    while (i < params->coder)
    {
        coder = malloc(sizeof(t_coder));
        if (!coder)
            return (destroy_coders(&coders, i));
        coder->id = i;
        coder->dongle_l = &dongles[get_dongle(i, params->coder, LEFT)];
        coder->dongle_r = &dongles[get_dongle(i, params->coder, RIGHT)];
        coder->mutex_dashboard = &dashboard_mu[i];
        coder->compilation_dashboard = &dashboard[i];
        /* give a copy of param to each coder avoid to use mutex for read param value */
        ft_memcopy(params, &coder->params, sizeof(t_params));
        coders[i] = coder;
        i++;
    }
    coders[i] = NULL;
    display_coders(coders);
    return (coders);
}

int thead_luncher(t_params *param, mutex_t *dongles, mutex_t *dashboard_mu)
{

    size_t          i;
    /* CODER_MAX is the num of thread max  -1 for the monitoring thread les see to reduce de max philo to 200 (evalsheet max)*/
    pthread_t       thread_coders[2000];
    pthread_t       thread_monitoring;
    t_coder         **coders;
    t_monitoring    monitoring_data;
    int             *dashboard;

    dashboard = malloc(sizeof(int) * param->coder);
    if(!dashboard)
        return (FALSE);
    memset(dashboard, 0, sizeof(int) * param->coder);
    coders = init_coder(param, dongles, dashboard_mu, dashboard);
    if(!coders)
    {
        free(dashboard);
        return (FALSE);
    }
    monitoring_data.dashboard = dashboard;
    monitoring_data.dashboard_mu = dashboard_mu;
    monitoring_data.nb_coder = param->coder;
    monitoring_data.ttb = param->ttb;
    if(pthread_create(&thread_monitoring, NULL, monitoring_thread, &monitoring_data) != 0)
    {
        perror("thread monitoring creation error");
        return(FALSE);
    }
    i = 0;
    while (i < param->coder)
    {
        printf("start thread %ld\n", i);
        pthread_create(&thread_coders[i], NULL, coder_thread, coders[i]);
        usleep(10);
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
