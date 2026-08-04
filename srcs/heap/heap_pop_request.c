/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop_request.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 11:57:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 01:53:22 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static int	remove_request(t_request **arr_request, size_t size_queue, int queue_type)
{
	size_t		i;

	swap_request(&arr_request[size_queue - 1], &arr_request[0]);
	arr_request[size_queue - 1] = NULL;
	size_queue--;
	i = 0;
	while (i < size_queue - 1)
	{
		if (queue_type == FIFO && arr_request[i]->request_id > arr_request[i + 1]->request_id)
			swap_request(&arr_request[i], &arr_request[i + 1]);
		else if (queue_type == EDF &&
			arr_request[i]->last_compilation + arr_request[i]->ttb <
			arr_request[i + 1]->last_compilation + arr_request[i]->ttb)
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
	remove_request(arr, request_queue->size, request_queue->queue_type);
	request_queue->size--;
	plug_heap_nodes(arr, request_queue->size);
	*request_queue->request_queue = arr[0];
	free(arr);
	return (TRUE);
}
