/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push_request.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 11:56:40 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 03:20:28 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	add_request(t_request **arr, size_t queue_size, int queue_type)
{
	size_t		i;
	t_request	*current;
	t_request	*parent;

	i = queue_size - 1;
	while (i > 0)
	{
		current = arr[i];
		parent = arr[i / 2];
		if (queue_type == FIFO && current->request_id < parent->request_id)
			swap_request(&arr[i], &arr[i / 2]);
		else if (queue_type == EDF
			&& current->last_compilation + current->ttb
			> parent->last_compilation + parent->ttb)
			swap_request(&arr[i], &arr[i / 2]);
		i = i / 2;
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
	add_request(arr, request_queue->size, request_queue->queue_type);
	plug_heap_nodes(arr, request_queue->size);
	*(request_queue->request_queue) = arr[0];
	free(arr);
	return (TRUE);
}
