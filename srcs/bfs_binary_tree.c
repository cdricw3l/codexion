/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_binary_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:49:46 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/29 12:04:16 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void push(t_request **queue, t_request *node)
{
    int i;

    i = 0;
    while (queue[i])
        i++;
    queue[i] = node;
}

static void pop(t_request **queue)
{
    int i;

    i = 0;
    if(!*queue)
        return ;
    while (queue[i])
    {
        queue[i] = queue[i + 1];
        i++; 
    }
}

static int queue_is_empty(t_request **queue)
{
    if(!queue)
        return (TRUE);
    if (!(*queue))
        return (TRUE);
    return (FALSE);
}

t_request **bfs_binary_tree_as_arr(t_queue *request_queue)
{
    t_request **queue;
    t_request **arr;
    t_request *tmp;
    
    if(!request_queue)
        return(NULL) ;
    queue = malloc(sizeof(t_request * ) *  request_queue->size);
    if(!queue)
        return(NULL);
    arr = malloc(sizeof(t_request *) *  (request_queue->size + 1));
    if(!arr)
    {
        free(queue);
        return (NULL);
    }
    memset(queue, 0, sizeof(t_request * ) * request_queue->size);
    memset(arr, 0, sizeof(t_request * ) * (request_queue->size + 1));
    push(queue, request_queue->request_queue[0]);
    while (!queue_is_empty(queue))
    {
        tmp = queue[0];
        /* create an  bfs array representation of the binary tree */
        push(arr, tmp);
        pop(queue);
        push(queue, tmp->left);
        push(queue, tmp->right);
    }
    free(queue);
    return (arr);
}

void swap_request(t_request **r1, t_request **r2)
{
    t_request *tmp;

    tmp = *r1;
    *r1 = *r2;
    *r2 = tmp;
}

void insert_request(t_queue *request_queue, t_request *request)
{
    int i;
    t_request **arr;
    //t_request *parent;
    //t_request *current;

    arr = bfs_binary_tree_as_arr(request_queue);
    if(!arr)
        return ;
    arr[request_queue->size] = request;
    i = request_queue->size;
    while (i > 0)
    {
        t_request *current = arr[i]; 
        t_request *parent  = arr[i / 2];
        if(current->request_id < parent->request_id)
            swap_request(&arr[i], &arr[i / 2]);
        i = i / 2;
    }
    while (arr[i])
    {
        size_t idx_left = (2 * i) + 1;
        size_t idx_right = (2 * i) + 2;

        if(idx_left <= request_queue->size)
            arr[i]->left = arr[idx_left]; 
        if(idx_right <= request_queue->size)
            arr[i]->right = arr[idx_right]; 
        i++;
    }
    i = 0;
    
    while (arr[i])
    {
        printf("request id %d\n", arr[i]->request_id);
        i++;
    }
    
    free(arr);
    request_queue->size++;
    
}