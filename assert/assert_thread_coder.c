/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread_coder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:16:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/02 20:31:24 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

#define NB_REQUEST 2
#define NB_CODER 2
#define NB_CR 10

int set_params(int *params)
{
    params[number_of_coders] = NB_CODER;
    params[time_to_burnout] = 450;
    params[time_to_compile] = 200;
    params[time_to_debug] = 100;
    params[time_to_refactor] = 100;
    params[number_of_compiles_required] = NB_CR;
    params[dongle_cooldown] = 10;
    params[scheduler] = FIFO ;
    return (TRUE);
}


void set_timestamp(t_coder *coder, timespec_t *timestamp)
{
    
    pthread_mutex_lock(coder->coder_mutex.timestamp_f);
    
    coder->last_compilation = timestamp;
    
    pthread_mutex_unlock(coder->coder_mutex.timestamp_f);
    
}

int create_and_send_request(t_coder *coder)
{
    t_request *request;

    request = create_request(coder);
    if(!request)
    {
        set_timestamp(coder, NULL);
        return(FALSE);
    }
    if(!push_request(coder->queue , request))
    {
        printf("Error creation request %d\n", request->request_id);
        set_timestamp(coder, NULL);
        return (FALSE);
    }
    (coder->queue->request_counter)++;
    return (TRUE);
}


int can_compile(t_coder *coder)
{

    if (!*(coder->queue->request_queue))
        return (FALSE);
    if (coder->queue->request_queue[0]->coder_id == coder->id)
        return (TRUE);
    return(FALSE);
    
}


void *coder_asser_routine(void *data)
{

    int i;
    t_coder *coder;
    t_request *request;

    i = 0;
    coder = (t_coder * )data;
    while (i < coder->params[number_of_compiles_required])
    {
        pthread_mutex_lock(&coder->queue->queue_lock);
        create_and_send_request(coder);

        pthread_cond_broadcast(coder->cond);
        while (!can_compile(coder))
        {
            pthread_cond_wait(coder->cond, &coder->queue->queue_lock);
        }
        if(*coder->queue->request_queue)
        {
            request = coder->queue->request_queue[0];
            pop_request(coder->queue);
            free(request);
        }
        pthread_cond_broadcast(coder->cond);
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
        
        safe_print(*coder, DEBBUG);
        usleep(coder->params[time_to_debug] * 1000);
        safe_print(*coder, REFACTO);
        usleep(coder->params[time_to_refactor] * 1000);
        i++;
    }
    return (NULL);
}   


int check_last_compilation(t_monitoring *monitor)
{
    int i;
    int j;
    timespec_t timestamp;

    i = 0;
    pthread_mutex_lock(monitor->timestamp_f);

    while (i < monitor->nb_coder)
    {
        clock_gettime(CLOCK_REALTIME, &timestamp);
        if(time_calculation(time_diff(*(monitor->last_compilations[i]), timestamp)) > monitor->ttb)
        {
            j = 0;
            while (j < monitor->nb_coder)
            {
                monitor->last_compilations[j] = NULL;
                j++;
            }
            pthread_mutex_unlock(monitor->timestamp_f);
            return (i + 1);
        }
    }
    pthread_mutex_unlock(monitor->timestamp_f);
    return (0);
}

void *thread_monitoring(void *data)
{

    t_monitoring *monitor;
    int dead_coder;
    
    monitor = (t_monitoring *)data;
    while (1)
    {
        dead_coder = check_last_compilation(monitor);
        if(dead_coder)
        {
            printf("coder %d is dead\n", dead_coder);
            return (NULL);
        }
    }
    return (NULL);
}


int launch_coder_assert(t_coder *coders, int nb_coder, t_monitoring *monitor)
{
    int i;
    pthread_t *thread;
    pthread_t mo;
    timespec_t now;

    thread = malloc(sizeof(pthread_t) * nb_coder);
    assert(thread);
    i = 0;
    clock_gettime(CLOCK_MONOTONIC, &now);
    //pthread_create(&mo, NULL, thread_monitoring, monitor);
    while (i < nb_coder)
    {
        coders[i].start = now;
        coders[i].last_compilation = &now;
        pthread_create(&thread[i], NULL, coder_asser_routine, &coders[i]);
        i++;
    }
    i = 0;
    while (i < nb_coder)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
    //pthread_join(mo, NULL);
    free(thread);
    return (TRUE);
    
}

int thread_coders_assert(void)
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
	if (!monitoring_initialisation(params[number_of_coders], &monitoring , &global_mu))
		return (mutex_destroy(params[number_of_coders], &global_mu));
	request_queue = queue_initialisation();
    assert(request_queue);
	if (!request_queue)
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	coders = coders_initialisation((int *)params, &global_mu, &monitoring, request_queue);
	assert(coders);
    if (!coders)
	{
		clean_queue(request_queue);
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	}
	display_coders(coders, params[number_of_coders]);
    launch_coder_assert(coders, params[number_of_coders], &monitoring);
    clean_queue(request_queue);
    clean_memory(params[number_of_coders], &global_mu, &monitoring);
    free(coders);





    END_TEST(__func__);
    return (TRUE);
}

