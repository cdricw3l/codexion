/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_binary_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:49:46 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/29 09:15:08 by cebouhad         ###   ########.fr       */
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

void bfs_binary_tree(t_queue *request_queue)
{
    t_request **queue;
    t_request *tmp;
    
    if(!request_queue)
        return ;
    queue = malloc(sizeof(t_request * ) *  request_queue->size);
    if(!queue)
        return ;
    push(queue, request_queue->request_queue[0]);
    while (!queue_is_empty(queue))
    {
        tmp = queue[0];
        printf("id: %d\n", tmp->request_id);
        pop(queue);
        push(queue, tmp->left);
        push(queue, tmp->right);
    }
    free(queue);
}