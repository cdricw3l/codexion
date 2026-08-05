/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:08:09 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 17:18:50 by cebouhad         ###   ########.fr       */
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
	t_coder		*coder;
	coder = (t_coder *)data;
	
	assert(coder->nb_of_compil == 0 && coder->params[number_of_compiles_required] == 2);
	while (coder->nb_of_compil < coder->params[number_of_compiles_required])
	{
		pthread_mutex_lock(&coder->queue->queue_lock);
		create_and_send_request(coder);
		pthread_mutex_unlock(&coder->queue->queue_lock);

		pthread_mutex_lock(coder->coder_mutex.can_compile_mu);
		while (*coder->can_compile == FALSE)
		{
			pthread_mutex_lock(coder->coder_mutex.display_f);
			printf("coder %d can compile \n", coder->id);
			pthread_mutex_unlock(coder->coder_mutex.display_f);

			pthread_cond_wait(coder->can_compile_cond, coder->coder_mutex.can_compile_mu);
		}
		pthread_mutex_unlock(coder->coder_mutex.can_compile_mu);
		compile(coder);
		debbug(coder);
		refactor(coder);
	}
	
	return (NULL);
}
