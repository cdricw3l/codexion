/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 09:31:30 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 13:36:04 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


t_request **queue_initialisation(void)
{
	t_request **queue;

	queue = malloc(sizeof(t_request *));
	if (!queue)
		return (NULL);
	*queue = NULL;
	return (queue);
}

static t_coder_mutex get_coder_mutex(int id, int nb_coder, t_global_mutex *global_mu)
{
	t_coder_mutex coder_mu;
	t_dongle left;
	t_dongle right;
	
	coder_mu.display_f = &global_mu->display_f;
	coder_mu.timestamp_f = &global_mu->timestamp_f;
	left.dongle = &global_mu->dongles[get_dongle(id, nb_coder, LEFT)];
	left.last_use = 0;
	right.dongle = &global_mu->dongles[get_dongle(id, nb_coder, RIGHT)];
	right.last_use = 0;
	coder_mu.dongle_l = left; 
	coder_mu.dongle_r = right; 
	return (coder_mu);
}


t_coder *coders_initialisation(int *params, t_global_mutex *global_mu, t_monitoring *monitor, t_request **queue)
{
	int 	i;
	t_coder *coders;


	coders = malloc(sizeof(t_coder) * params[number_of_coders]);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < params[number_of_coders])
	{
		coders[i].id = i + 1;
		ft_memcopy(params, &coders[i].params, sizeof(int) * 8);
		coders[i].coder_mutex = get_coder_mutex(i, params[number_of_coders], global_mu);
		coders[i].last_compilation = &monitor->last_compilations[i];
		coders[i].cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
		coders[i].queue = queue;
		i++;
	}
	return (coders);
}

int monitoring_initialisation(int nb_coder, t_monitoring *monitoring, t_global_mutex *global_mu)
{
	monitoring->last_compilations = malloc(sizeof(clock_t) * nb_coder);
	if(!monitoring->last_compilations)
		return (FALSE);
	memset(monitoring->last_compilations, 0, sizeof(clock_t) * nb_coder);
	monitoring->display_f =  &global_mu->display_f;
	monitoring->timestamp_f = &global_mu->timestamp_f;
	return (TRUE);
}

int mutex_initialisation(int nb_coder, t_global_mutex *global_mu)
{
	int	i;

	global_mu->dongles = malloc(sizeof(pthread_mutex_t) * nb_coder);
	if(!global_mu->dongles)
		return (FALSE);
	i = 0;
	while (i < nb_coder)
	{
		global_mu->dongles[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER; 
		i++;
	}
	global_mu->display_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	global_mu->timestamp_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (TRUE);
}
