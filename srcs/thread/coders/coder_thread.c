/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:08:09 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/04 23:17:25 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

int	can_compile(t_coder *coder)
{
	t_request	*request;
	
	if (!*(coder->queue->request_queue))
		return (FALSE);
	request = coder->queue->request_queue[0];
	
	//printf("coder %d ask for compilation\n", coder->id);
	if (coder->queue->request_queue[0]->coder_id == coder->id)
	{
		//printf("Status [OK]\n");
		if (*coder->queue->request_queue)
		{
			//printf("NExt request %d\n", coder->queue->request_queue[0]->left->coder_id);
			pop_request(coder->queue);
			free(request);
		}
		compile(coder);
		return(TRUE);
	}
	//printf("Status [NOK]\n");
	return (FALSE);
}

int	create_and_send_request(t_coder *coder)
{
	t_request	*request;

	request = create_request(coder);
	if (!request)
		return (FALSE);
	if (!push_request(coder->queue, request))
	{
		printf("Error creation request %d\n", request->request_id);
		return (FALSE);
	}
	(coder->queue->request_counter)++;
	return (TRUE);
}

int	check_state(t_coder *coder)
{
	int	status;

	status = TRUE;
	pthread_mutex_lock(coder->coder_mutex.state);
	if (coder->state == FALSE)
		status = FALSE;
	pthread_mutex_unlock(coder->coder_mutex.state);
	return (status);
}

void	action(t_coder *coder)
{
	
	debbug(coder);
	refactor(coder);
}

void	*coder_routine(void *data)
{
	int			i;
	t_coder		*coder;
	//t_request	*request;
	int start;
	
	i = 0;
	coder = (t_coder *)data;
	start = FALSE;
	while (!start)
	{
		pthread_mutex_lock(coder->coder_mutex.state);
		start = (coder->state == TRUE); 
		pthread_mutex_unlock(coder->coder_mutex.state);
		if (start)
			break ;
	}
	
	while (i < coder->params[number_of_compiles_required] && check_state(coder))
	{
		pthread_mutex_lock(&coder->queue->queue_lock);
		create_and_send_request(coder);
		pthread_cond_broadcast(&coder->queue->cond);
		while (!can_compile(coder))
			pthread_cond_wait(&coder->queue->cond, &coder->queue->queue_lock);
		// if (*coder->queue->request_queue)
		// {
		// 	request = coder->queue->request_queue[0];
		// 	//printf("NExt request %d\n", coder->queue->request_queue[0]->left->coder_id);
		// 	pop_request(coder->queue);
		// 	free(request);
		// }
		pthread_mutex_unlock(&coder->queue->queue_lock);
		pthread_cond_broadcast(&coder->queue->cond);
		action(coder);
		i++;
	}
	return (NULL);
}
