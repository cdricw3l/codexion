/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:54:23 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 14:54:49 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_queue	*queue_init(int type, int ttb)
{
	t_queue	*request_queue;

	request_queue = malloc(sizeof(t_queue));
	if (!request_queue)
		return (queue_err(QUEUE_ERR));
	request_queue->request_queue = malloc(sizeof(t_request *));
	if (!request_queue)
	{
		free(request_queue);
		return (queue_err(QUEUE_ERR));
	}
	request_queue->queue_type = type;
	request_queue->ttb = ttb;
	request_queue->size = 0;
	request_queue->request_counter = 0;
	*(request_queue->request_queue) = NULL;
	if (pthread_mutex_init(&request_queue->queue_lock, NULL)
		|| pthread_cond_init(&request_queue->cond, NULL))
	{
		free(request_queue->request_queue);
		free(request_queue);
		return (NULL);
	}
	return (request_queue);
}