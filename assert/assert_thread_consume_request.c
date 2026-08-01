/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread_consume_request.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:16:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/01 14:31:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

#define NB_REQUEST 10



void *queue_routine_remove_request(void *arg)
{
    t_queue *queue;
    int i = 0;
    int j;
    queue = (t_queue *)arg;
    while (i < NB_REQUEST)
    {
        pthread_mutex_lock(&queue->queue_lock);
        if (send_request(queue) == FALSE)
            return (NULL);
        pthread_mutex_unlock(&queue->queue_lock);
        sleep(1);
        pthread_mutex_lock(&queue->queue_lock);
        if (remove_request(queue) == FALSE)
            return (NULL);
        pthread_mutex_unlock(&queue->queue_lock);
        i++;
    }
    return (NULL);
}

#define NB_CODER 2

int thread_consume_request_assert(void)
{
    START_TEST(__func__);
    t_queue *queue;
    pthread_t thread[NB_CODER];
    int i;


    queue = queue_initialisation();
    assert(queue);
    for (i = 0; i < NB_CODER; i++)
        pthread_create(&thread[i], NULL, queue_routine_remove_request, queue);
    for (i = 0; i < NB_CODER; i++)
        pthread_join(thread[i], NULL);

    t_request **arr;
    arr =  bfs_binary_tree_as_arr(queue);
    for (int j = 0; j < queue->size; j++)
    {
        printf(YELB"START CHECK"CRESET"\n");
        display_request(*(arr[j]));
        assert(arr[j]->request_id == j);
        free(arr[j]);
    }
    free(arr);
    free(queue->request_queue);
    free(queue);
    END_TEST(__func__);
    return (TRUE);
}

