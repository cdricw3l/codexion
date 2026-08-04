/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:08:09 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/04 12:16:23 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int can_compile(t_coder *coder)
{

    if (!*(coder->queue->request_queue))
        return (FALSE);
    return(coder->queue->request_queue[0]->coder_id == coder->id);
    
}

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

int check_state(t_coder *coder)
{
    int status;

    status = TRUE;
    pthread_mutex_lock(coder->coder_mutex.state);
    if(coder->state == FALSE)
        status = FALSE;
    pthread_mutex_unlock(coder->coder_mutex.state);
    return (status);
}

void *coder_routine(void *data)
{

    int i;
    t_coder *coder;
    t_request *request;

    i = 0;
    coder = (t_coder * )data;
   
    while (i < coder->params[number_of_compiles_required]  && check_state(coder))
    {
        
        pthread_mutex_lock(&coder->queue->queue_lock);
        create_and_send_request(coder);

        pthread_cond_broadcast(&coder->queue->cond);
        while (!can_compile(coder))
        {
            pthread_cond_wait(&coder->queue->cond, &coder->queue->queue_lock);
        }
        if(*coder->queue->request_queue)
        {
            printf("coder %d pop queue\n", coder->id);

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
        pthread_mutex_lock(coder->coder_mutex.timestamp_f);
        set_timestamp(coder);
        pthread_mutex_unlock(coder->coder_mutex.timestamp_f);
        
        safe_print(*coder, DEBBUG);
        usleep(coder->params[time_to_debug] * 1000);
        safe_print(*coder, REFACTO);
        usleep(coder->params[time_to_refactor] * 1000);
        i++;
    }
    printf("coder %d compile: %d/%d\n", coder->id, coder->nb_of_compil , coder->params[number_of_compiles_required]);
    assert(coder->nb_of_compil == coder->params[number_of_compiles_required]);
    return (NULL);
}