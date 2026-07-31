/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:16:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 21:48:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

#define NB_REQUEST 2

t_request *_request(int id_request, int id_coder)
{
    t_request *request;

    request = malloc(sizeof(t_request));
    assert(request);
    request->request_id = id_request;
    request->coder_id = (int)id_coder;
    request->last_compilation = 0;
    request->left = NULL;
    request->right = NULL;
    return (request);
}


void *queue_routine(void *arg)
{
    t_queue *queue;
    t_request *request;
    int i = 0;
    int j;
    queue = (t_queue *)arg;
    while (i < NB_REQUEST)
    {

        pthread_mutex_lock(&queue->queue_lock);
        request = _request(queue->request_counter, pthread_self());
        if(!push_request(queue, request))
        {
            printf("Error creation request %d\n", request->request_id);
            return (NULL);
        }
        printf("thread %ld pushed the request %zu new len %zu\n", pthread_self(), queue->request_counter ,queue->size);
        queue->request_counter++;
        pthread_mutex_unlock(&queue->queue_lock);
        sleep(1);
        i++;
    }
    return (NULL);
    
}


#define NB 2

int thread_request_assert(void)
{
    START_TEST(__func__);
    t_queue *queue;
    pthread_t thread[NB];
    int i;


    queue = malloc(sizeof(t_queue));
    assert(queue);
    if(!queue_initialisation(queue))
        return (FALSE);
    for (i = 0; i < NB; i++)
        pthread_create(&thread[i], NULL, queue_routine, queue);
    for (i = 0; i < NB; i++)
        pthread_join(thread[i], NULL);

    t_request **arr;

    arr =  bfs_binary_tree_as_arr(queue);
    for (int j = 0; j < queue->size; j++)
    {
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

