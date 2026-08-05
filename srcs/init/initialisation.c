/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 09:31:30 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 04:11:55 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_queue	*queue_init(int type, int ttb)
{
	t_queue	*request_queue;

	request_queue = malloc(sizeof(t_queue));
	if (!request_queue)
	{
		write(STDERR_FILENO, "Error init queue\n", strlen("Error init queue\n"));
		return (NULL);
	}
	request_queue->request_queue = malloc(sizeof(t_request *));
	if (!request_queue)
	{
		write(STDERR_FILENO, "Error init queue\n", strlen("Error init queue\n"));
		free(request_queue);
		return (FALSE);
	}
	request_queue->queue_type = type;
	request_queue->ttb = ttb;
	request_queue->size = 0;
	request_queue->request_counter = 0;
	*(request_queue->request_queue) = NULL;
	request_queue->queue_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	request_queue->cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	return (request_queue);
}

static t_coder_mutex	get_coder_mutex(int id,
	int nb_coder, t_global_mutex *global_mu)
{
	t_dongle		left;
	t_dongle		right;
	t_coder_mutex	coder_mu;

	coder_mu.display_f = &global_mu->display_f;
	coder_mu.timestamp_f = &global_mu->timestamp_f;
	coder_mu.state = &global_mu->state[id];
	left.dongle = &global_mu->dongles[get_dongle(id, nb_coder, LEFT)];
	left.last_use = 0;
	right.dongle = &global_mu->dongles[get_dongle(id, nb_coder, RIGHT)];
	right.last_use = 0;
	coder_mu.dongle_l = left; 
	coder_mu.dongle_r = right;
	return (coder_mu);
}

t_coder	*coders_init(int *params, t_global_mutex *global_mu, t_queue *queue)
{
	int		i;
	t_coder	*coders;

	coders = malloc(sizeof(t_coder) * params[nbc]);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < params[nbc])
	{
		coders[i].id = i + 1;
		ft_memcopy(params, coders[i].params, sizeof(int) * 8);
		coders[i].coder_mutex = get_coder_mutex(i, params[nbc], global_mu);
		coders[i].nb_of_compil = 0;
		coders[i].queue = queue;
		i++;
	}
	return (coders);
}

t_monitoring	*monitoring_init(int *params,
	t_global_mutex *global_mu, t_coder *coder)
{
	t_monitoring	*monitoring;

	monitoring = malloc(sizeof(t_monitoring));
	if (!monitoring)
		return (NULL);
	monitoring->last_compilations = malloc(sizeof(clock_t) * params[nbc]);
	if (!monitoring->last_compilations)
	{
		free(monitoring);
		return (NULL);
	}
	memset(monitoring->last_compilations, -1, sizeof(clock_t) * params[nbc]);
	monitoring->display_f = &global_mu->display_f;
	monitoring->timestamp_f = &global_mu->timestamp_f;
	monitoring->nb_coder = params[nbc];
	monitoring->coder = coder;
	ft_memcopy(params, monitoring->params, sizeof(int) * 8);
	monitoring->state = global_mu->state;
	return (monitoring);
}

int	mutex_init(int nb_coder, t_global_mutex *global_mu)
{
	int	i;

	global_mu->dongles = malloc(sizeof(pthread_mutex_t) * nb_coder);
	if (!global_mu->dongles)
		return (FALSE);
	global_mu->state = malloc(sizeof(pthread_mutex_t) * nb_coder);
	if (!global_mu->state)
	{
		free(global_mu->dongles);
		return (FALSE);
	}
	i = 0;
	while (i < nb_coder)
	{
		global_mu->dongles[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		global_mu->state[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
	global_mu->display_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	global_mu->timestamp_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (TRUE);
}
