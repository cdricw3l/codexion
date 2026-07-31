/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:09:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 15:58:51 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"


t_request create_request(t_coder *coder)
{
    t_request request;

    request.coder_id = coder->id;
    request.request_id = coder->queue->request_counter;
    request.coder_cond_l = &coder->cond_left;
    request.coder_cond_r = &coder->cond_right;
    request.dongle_left = coder->coder_mutex.dongle_l.dongle;
    request.dongle_right = coder->coder_mutex.dongle_r.dongle;
    request.last_compilation = *coder->last_compilation;
    request.left = NULL;
    request.right = NULL;
    return (request);
}

void *coder_routine(void *data)
{
    t_coder *coder;
    t_request request;
    int i;

    i = 0;
    coder = (t_coder *)data;
    while (i < 5)
    {
        pthread_mutex_lock(coder->coder_mutex.dongle_r.dongle);
        pthread_mutex_lock(coder->coder_mutex.dongle_l.dongle);
        request = create_request(coder);
        printf("coder : %d, loop: %d\n", coder->id, i);
        push_request(coder->queue, &request);
        coder->queue->request_counter++;
        display_tree(*coder->queue->request_queue);
        printf("\n");
        sleep(1);
        pthread_mutex_unlock(coder->coder_mutex.dongle_l.dongle);
        pthread_mutex_unlock(coder->coder_mutex.dongle_r.dongle);
        i++;
        sleep(1);
    }
    return (NULL);
}

int thread_launcher(t_coder *coder, t_monitoring *monitor, int nb_coder)
{
    int i;
    pthread_t *threads;

    
    if(!coder || !monitor)
        return(FALSE);
    threads = malloc(sizeof(pthread_t) * nb_coder);
    if(!threads)
        return (FALSE);
    i = 0;
    
    while (i < nb_coder)
    {

        pthread_create(&threads[i], NULL, coder_routine, &coder[i]);
        sleep(1);
        i++;
    }
    i = 0;
    while (i < nb_coder)
    {
        pthread_join(threads[i], NULL);    
        i++;
    }
    return (TRUE);
}