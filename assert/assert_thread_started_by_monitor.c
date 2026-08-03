/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread_started_by_monitor.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 10:25:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/03 11:43:54 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

int can_start(t_coder *coder)
{
    int start;

    start = FALSE;
    pthread_mutex_lock(coder->coder_mutex.timestamp_f);
    if (*(coder->last_compilation) == 0)
        start = TRUE;
    pthread_mutex_unlock(coder->coder_mutex.timestamp_f);
    return (start);
}

int check_timestamp(clock_t last_c, int time_to_burnout)
{
    timespec_t  now;
    clock_t     now_in_nano;
    int         diff;

    clock_gettime(CLOCK_MONOTONIC, &now);
    now_in_nano = (now.tv_nsec + second_to_nano(now.tv_sec));
    diff = nano_to_ms(now_in_nano - last_c);
    printf("last/ttb : %d/%d\n", diff, time_to_burnout); 
    if(diff > time_to_burnout)
        return (FALSE);
    return (TRUE);
}

void *monitor_assert(void *data)
{
    int i;
    t_monitoring *monitor;
    timespec_t start;
    
    monitor = (t_monitoring *)data;
    i = 0;
    pthread_mutex_lock(monitor->timestamp_f);
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (i < monitor->nb_coder)
    {
        
        monitor->coder[i].start = start;
        monitor->last_compilations[i] = 0;
        i++;
    }
    pthread_mutex_unlock(monitor->timestamp_f);
    
    while (1)
    {
        i = 0;
        pthread_mutex_lock(monitor->timestamp_f);
        while (i < monitor->nb_coder)
        {
            printf("here\n");

            pthread_mutex_lock(monitor->display_f);
            if(!check_timestamp(monitor->last_compilations[i], monitor->ttb))
                printf("The coder %d is dead \n", i+1);
            pthread_mutex_unlock(monitor->display_f);
            i++;
        }
        pthread_mutex_unlock(monitor->timestamp_f);
        usleep(30000);
    }
    return (NULL);
}

void *wait_coder_routine(void *data)
{

    int i;
    t_coder *coder;
    t_request *request;

    i = 0;
    coder = (t_coder * )data;
    while (!can_start(coder))
    {
        printf("coder %d is waiting\n", coder->id);
        usleep(50000);
    }
    printf("coder start is routine\n");
    while (i < coder->params[number_of_compiles_required])
    {
        pthread_mutex_lock(&coder->queue->queue_lock);
        create_and_send_request(coder);

        //pthread_cond_broadcast(&coder->queue->cond);
        while (!can_compile(coder))
        {
            pthread_cond_wait(&coder->queue->cond, &coder->queue->queue_lock);
        }
        if(*coder->queue->request_queue)
        {
            request = coder->queue->request_queue[0];
            pop_request(coder->queue);
            free(request);
        }
        //pthread_cond_broadcast(&coder->queue->cond);
        pthread_mutex_unlock(&coder->queue->queue_lock);

        if(coder->id == 1 ||  coder->id == coder->params[number_of_coders])
        {
            pthread_mutex_lock(coder->coder_mutex.dongle_r.dongle);
            pthread_mutex_lock(coder->coder_mutex.dongle_l.dongle);
        }
        else
        {
            pthread_mutex_lock(coder->coder_mutex.dongle_l.dongle);
            pthread_mutex_lock(coder->coder_mutex.dongle_r.dongle);
        }
        safe_print(*coder, TAKE);
        safe_print(*coder, COMPILE);
        usleep(coder->params[time_to_compile] * 1000);
        if(coder->id == 1 ||  coder->id == coder->params[number_of_coders])
        {
            pthread_mutex_unlock(coder->coder_mutex.dongle_r.dongle);
            pthread_mutex_unlock(coder->coder_mutex.dongle_l.dongle);
        }
        else
        {
            pthread_mutex_unlock(coder->coder_mutex.dongle_l.dongle);
            pthread_mutex_unlock(coder->coder_mutex.dongle_r.dongle);
        }
        set_timestamp(coder);
        safe_print(*coder, DEBBUG);
        usleep(coder->params[time_to_debug] * 1000);
        safe_print(*coder, REFACTO);
        usleep(coder->params[time_to_refactor] * 1000);
        i++;
    }
    return (NULL);
}

int launch_coder_and_monitoring_assert(t_coder *coders, int nb_coder, t_monitoring *monitor)
{
    int         i;
    pthread_t   *thread_coder;
    pthread_t   thread_monitor;
    timespec_t  now;

    thread_coder = malloc(sizeof(pthread_t) * nb_coder);
    assert(thread_coder);
    i = 0;
    clock_gettime(CLOCK_MONOTONIC, &now);
    while (i < nb_coder)
    {
        coders[i].last_compilation  = &monitor->last_compilations[i];
        assert(*(coders[i].last_compilation) == -1);
        pthread_create(&thread_coder[i], NULL, wait_coder_routine, &coders[i]);
        //usleep(50000);
        i++;
    }
    pthread_create(&thread_monitor, NULL, monitor_assert, monitor);
    i = 0;
    while (i < nb_coder)
        pthread_join(thread_coder[i++], NULL);
    pthread_join(thread_monitor, NULL);
    free(thread_coder);
    return (TRUE);
    
}

int thread_coders_and_monitor_assert(void)
{
    START_TEST(__func__);
    int 			params[8];
	t_coder			*coders;
	t_global_mutex	global_mu;
	t_monitoring	monitoring;
	t_queue			*request_queue;
    
    assert(set_params(params));
    display_params(params);
    if(!mutex_initialisation(params[number_of_coders], &global_mu))
		return (write(STDERR_FILENO, "Error initialisation mutex\n", strlen("Error initialisation mutex\n")));
	
	//display_mutex_data(params[number_of_coders], global_mu);
	request_queue = queue_initialisation();
    assert(request_queue);
	if (!request_queue)
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	coders = coders_initialisation((int *)params, &global_mu, request_queue);
	assert(coders);
    if (!coders)
	{
		clean_queue(request_queue);
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	}
    if (!monitoring_initialisation(params[number_of_coders], &monitoring , &global_mu, coders))
		return (mutex_destroy(params[number_of_coders], &global_mu));
    launch_coder_and_monitoring_assert(coders, params[number_of_coders], &monitoring);
    clean_queue(request_queue);
    clean_memory(params[number_of_coders], &global_mu, &monitoring);
    free(coders);

    END_TEST(__func__);
    return (TRUE);
}