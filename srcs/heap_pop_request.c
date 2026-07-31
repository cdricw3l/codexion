/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop_request.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 11:57:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 11:58:18 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static int	remove_request(t_request **arr_request, size_t size_queue)
{
	size_t		i;
	size_t		idx_left;
	size_t		idx_right;
	t_request	*children_r;
	t_request	*children_l;

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
