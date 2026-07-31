/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:49:12 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 11:50:27 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	swap_request(t_request **r1, t_request **r2)
{
	t_request	*tmp;

	tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}

void	add_request(t_request **arr, size_t queue_size)
{
	size_t		i;
	t_request	*current;
	t_request	*parent;

	i = queue_size - 1;
	while (i > 0)
	{

		current = arr[i];
		parent = arr[i / 2];
		if (current->request_id < parent->request_id)
			swap_request(&arr[i], &arr[i / 2]);
		i = i / 2;
	}
}

void	plug_heap_nodes(t_request **arr, size_t queue_size)
{
	size_t	i;
	size_t	idx_left;
	size_t	idx_right;

	i = 0;
	while (i < queue_size)
	{	
		idx_left = (2 * i) + 1;
		idx_right = (2 * i) + 2;
		if (idx_left < queue_size)
			arr[i]->left = arr[idx_left];
		else
			arr[i]->left = NULL;
		if (idx_right < queue_size)
			arr[i]->right = arr[idx_right];
		else
			arr[i]->right = NULL;
		i++;
	}
}

int	push_request(t_queue *request_queue, t_request *request)
{
	t_request	**arr;
	
	
	if (request_queue->size == 0)
	{
		*(request_queue->request_queue) = request;
		request_queue->size++;
		return (TRUE);
	}
	request_queue->size++;
	arr = bfs_binary_tree_as_arr(request_queue);
	if (!arr)
		return (FALSE);
	arr[request_queue->size - 1] = request;
		
	add_request(arr, request_queue->size);
	plug_heap_nodes(arr, request_queue->size);
	*(request_queue->request_queue) = arr[0];
	free(arr);
	return (TRUE);
}

static int remove_request(t_request **arr_request, size_t size_queue)
{
	size_t	i;
	size_t		idx_left;
	size_t		idx_right;
	t_request 	*children_r;
	t_request 	*children_l;
	
	swap_request(&arr_request[size_queue - 1], &arr_request[0]);
	arr_request[size_queue - 1] = NULL;
	size_queue--;
	i = 0;
	while (i < size_queue - 1)
	{
		if (arr_request[i]->request_id > arr_request[i + 1]->request_id)
			swap_request(&arr_request[i], &arr_request[i + 1]);
		i++;
	}
	return (TRUE);
}

int	pop_request(t_queue *request_queue)
{
	t_request	**arr;

	if (request_queue->size <= 0)
		return (FALSE);
	if (request_queue->size == 1)
	{
		*request_queue->request_queue = NULL;
		request_queue->size = 0;
		return (TRUE);
	}
	arr = bfs_binary_tree_as_arr(request_queue);
	if (!arr)
		return (FALSE);
	remove_request(arr, request_queue->size);
	request_queue->size--;
	plug_heap_nodes(arr, request_queue->size);
	*request_queue->request_queue = arr[0];
	free(arr);
	return (TRUE);
}