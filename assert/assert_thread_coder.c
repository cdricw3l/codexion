/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread_coder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:16:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/03 09:20:33 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"




int create_and_send_request(t_coder *coder)
{
    t_request *request;

    request = create_request(coder);
    if(!request)
        return(FALSE);
    if(!push_request(coder->queue , request))
    {
        printf("Error creation request %d\n", request->request_id);
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

        //pthread_cond_broadcast(coder->cond);
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
        //pthread_cond_broadcast(coder->cond);
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


int launch_coder_assert(t_coder *coders, int nb_coder, t_monitoring *monitor)
{
    int         i;
    pthread_t   *thread;
    timespec_t  now;

    thread = malloc(sizeof(pthread_t) * nb_coder);
    assert(thread);
    i = 0;
    clock_gettime(CLOCK_MONOTONIC, &now);
    while (i < nb_coder)
    {
        coders[i].start = now;
        pthread_create(&thread[i], NULL, coder_asser_routine, &coders[i]);
        usleep(50000);
        i++;
    }
    i = 0;
    while (i < nb_coder)
        pthread_join(thread[i++], NULL);
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

