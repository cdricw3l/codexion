/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread_started_by_monitor.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 10:25:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 01:48:57 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

int can_start(t_coder *coder)
{
    int start;

    start = FALSE;
    pthread_mutex_lock(coder->coder_mutex.state);
    if (coder->state == TRUE)
        start = TRUE;
    pthread_mutex_unlock(coder->coder_mutex.state);
    return (start);
}

int	create_and_send_request_assert(t_coder *coder)
{
	t_request	*request;

	request = create_request(coder);
	if (!request)
		return (FALSE);
	if (!push_request(coder->queue, request))
	{
		printf("Error creation request %d\n", request->request_id);
		return (FALSE);
	}
	(coder->queue->request_counter)++;
	return (TRUE);
}

int check_end_assert(t_coder *coder)
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

int check_timestamp_assert(t_coder *coder ,clock_t last_c, int *params)
{
    timespec_t  now;
    clock_t     now_in_nano;
    int         diff;

    clock_gettime(CLOCK_MONOTONIC, &now);
    now_in_nano = (now.tv_nsec + second_to_nano(now.tv_sec));
    diff = nano_to_ms(now_in_nano - last_c);
    if(diff > time_to_burnout && coder->nb_of_compil > 0 && coder->nb_of_compil < params[number_of_compiles_required])
    {
        //printf("%ld coder %d is nb compile: %d, reuqueired: %d\n", time_calculation(time_diff(coder->start, now)),coder->id, coder->nb_of_compil, params[number_of_compiles_required]);
        return (FALSE);
    }
    return (TRUE);
}

void *monitor_assert(void *data)
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
            pthread_mutex_lock(monitor->display_f);
            if(!check_timestamp_assert(&monitor->coder[i], monitor->last_compilations[i], monitor->params))
            {
                pthread_mutex_unlock(monitor->display_f);
                int j = 0;
                while (j < monitor->nb_coder)
                {
                    pthread_mutex_lock(monitor->coder[j].coder_mutex.state);
                    monitor->coder[j].coder_mutex.state = FALSE;
                    printf("coder %d is dead\n", monitor->coder[j].id);
                    j++;
                    return (NULL);
                }
            }
            i++;
            pthread_mutex_unlock(monitor->display_f);
        }
        pthread_mutex_unlock(monitor->timestamp_f);
        usleep(200000);

        if (check_end_assert(monitor->coder))
        {
            printf("check end ok\n");
            break;
        }
    }
    return (NULL);
}

int check_state_assert(t_coder *coder)
{
    int status;

    status = TRUE;
    pthread_mutex_lock(coder->coder_mutex.state);
    if(coder->state == FALSE)
        status = FALSE;
    pthread_mutex_unlock(coder->coder_mutex.state);
    return (status);
}
int	can_compile_assert(t_coder *coder)
{
	t_request	*request;
	
	if (!*(coder->queue->request_queue))
		return (FALSE);
	request = coder->queue->request_queue[0];
	// if(!check_cooldown(coder))
	// 	return (FALSE);
	//printf("coder %d ask for compilation\n", coder->id);
	if (coder->queue->request_queue[0]->coder_id == coder->id)
	{
		//printf("Status [OK]\n");
		if (*coder->queue->request_queue)
		{
			//printf("NExt request %d\n", coder->queue->request_queue[0]->left->coder_id);
			pop_request(coder->queue);
			free(request);
		}
		compile(coder);
		return(TRUE);
	}
	//printf("Status [NOK]\n");
	return (FALSE);
}


void *wait_coder_routine(void *data)
{

    int i;
    t_coder *coder;
    t_request *request;

    i = 0;
    coder = (t_coder * )data;
   
    while (i < coder->params[number_of_compiles_required]  && check_state_assert(coder))
    {
        
        pthread_mutex_lock(&coder->queue->queue_lock);
        create_and_send_request_assert(coder);

        pthread_cond_broadcast(&coder->queue->cond);
        while (!can_compile_assert(coder))
        {
            pthread_cond_wait(&coder->queue->cond, &coder->queue->queue_lock);
        }
        if(*coder->queue->request_queue)
        {
            request = coder->queue->request_queue[0];
            pop_request(coder->queue);
            free(request);
        }
        pthread_cond_broadcast(&coder->queue->cond);
        
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
        safe_print(*coder, TAKE, coder->coder_mutex.display_f);
        safe_print(*coder, COMPILE, coder->coder_mutex.display_f);
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
        pthread_mutex_lock(coder->coder_mutex.timestamp_f);
        set_timestamp(coder, TIMESTAMP_COMPILATION);
        pthread_mutex_unlock(coder->coder_mutex.timestamp_f);
        
        safe_print(*coder, DEBBUG, coder->coder_mutex.display_f);
        usleep(coder->params[time_to_debug] * 1000);
        safe_print(*coder, REFACTO, coder->coder_mutex.display_f);
        usleep(coder->params[time_to_refactor] * 1000);
        i++;
    }
    printf("coder %d compile: %d/%d\n", coder->id, coder->nb_of_compil , coder->params[number_of_compiles_required]);
    assert(coder->nb_of_compil == coder->params[number_of_compiles_required]);
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
        coders[i].start = now;
        coders[i].state = TRUE;
        pthread_create(&thread_coder[i], NULL, wait_coder_routine, &coders[i]);
        //usleep(50000);
        i++;
    }
    pthread_create(&thread_monitor, NULL, monitor_assert, monitor);
    pthread_join(thread_monitor, NULL);
    i = 0;
    while (i < nb_coder)
        pthread_join(thread_coder[i++], NULL);
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
	request_queue = queue_initialisation(params[scheduler], params[time_to_burnout]);
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
    if (!monitoring_initialisation((int *)params, &monitoring , &global_mu, coders))
		return (mutex_destroy(params[number_of_coders], &global_mu));
    launch_coder_and_monitoring_assert(coders, params[number_of_coders], &monitoring);
    // clean_queue(request_queue);
    // clean_memory(params[number_of_coders], &global_mu, &monitoring);
    // free(coders);

    END_TEST(__func__);
    return (TRUE);
}