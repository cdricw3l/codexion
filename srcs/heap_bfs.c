/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_bfs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:49:46 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/30 19:07:49 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	push(t_request **queue, t_request *node)
{
	int	i;

	i = 0;
	
	while (queue[i])
		i++;
	queue[i] = node;
}

void	pop(t_request **queue, int queue_size)
{
	int	i;

	if (!*queue)
		return ;
	i = 0;
	while (i < queue_size - 1)
	{
		queue[i] = queue[i + 1];
		i++; 
	}
	queue[i] = NULL;
}

static int	queue_is_empty(t_request **queue)
{
	if (!queue)
		return (TRUE);
	if (!(*queue))
		return (TRUE);
	return (FALSE);
}

static t_request	**get_heap_as_arr(t_queue *request_queue, t_request **queue)
{
	t_request	**arr;
	t_request	*tmp;
	int			queue_size;


	arr = malloc(sizeof(t_request *) * (request_queue->size));
	if (!arr)
		return (NULL);
	memset(arr, 0, sizeof(t_request *) * (request_queue->size));
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
	printf("here %zu\n", request_queue->size);

	return (arr);
}

t_request	**bfs_binary_tree_as_arr(t_queue *request_queue)
{
	t_request	**queue;
	t_request	**arr;


	if (!request_queue)
		return (NULL);
	queue = malloc(sizeof(t_request *) * (request_queue->size));
	if (!queue)
		return (NULL);
	memset(queue, 0, sizeof(t_request *) * (request_queue->size));
	arr = get_heap_as_arr(request_queue, queue);
	free(queue);
	return (arr);
}
