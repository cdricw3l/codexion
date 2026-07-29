/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_binary_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:49:46 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/29 15:28:30 by cebouhad         ###   ########.fr       */
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

static void pop(t_request **queue, int queue_size)
{
    int i;

    if(!*queue)
        return ;
    
    i = 0;
    while (i < queue_size)
    {
        //printf("adress %p\n", &queue[i + 1]);
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
    int queue_size;
    t_request **arr;
    t_request *tmp;
    
    if(!request_queue)
        return(NULL) ;
    queue = malloc(sizeof(t_request * ) *  (request_queue->size + 1));
    if(!queue)
        return(NULL);
    arr = malloc(sizeof(t_request *) *  (request_queue->size + 1));
    if(!arr)
    {
        free(queue);
        return (NULL);
    }
    memset(queue, 0, sizeof(t_request * ) * (request_queue->size + 1));
    memset(arr, 0, sizeof(t_request * ) * (request_queue->size + 1));
    push(queue, request_queue->request_queue[0]);
    queue_size = 1;
    while (!queue_is_empty(queue))
    {
        tmp = queue[0];
        /* create an  bfs array representation of the binary tree */
        push(arr, tmp);
        pop(queue, queue_size);
        queue_size--;
        push(queue, tmp->left);
        queue_size++;
        push(queue, tmp->right);
        queue_size++;
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


void display_r_arr(t_request **r)
{
    int i;

    i = 0;
    printf(GRN"Display arr"CRESET"\n");
    while (r[i])
    {
        printf("request id %d\n", r[i]->request_id);
        i++;
    }
    
}

void insert_request(t_queue *request_queue, t_request *request)
{
    size_t i;
    t_request **arr;

    if (request_queue->size == 0)
    {
        *(request_queue->request_queue) = request;
        request_queue->size++;
        return ;
    }
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
    i = 0;
    while (i <= request_queue->size)
    {
        size_t idx_left = (2 * i) + 1;
        size_t idx_right = (2 * i) + 2;

        if(idx_left <= request_queue->size + 1)
        {
            printf("left %zu\n", idx_left);
            arr[i]->left = arr[idx_left]; 
        }
        if(idx_right <= request_queue->size + 1)
        {
            printf("right %zu\n", idx_right);
            arr[i]->right = arr[idx_right];
        }
        else
        {
            arr[i]->left = NULL;
            arr[i]->right = NULL;
        }
        i++;
    }
    *(request_queue->request_queue) = arr[0];
    free(arr);
    request_queue->size++;
}