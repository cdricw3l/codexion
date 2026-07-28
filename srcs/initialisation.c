/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 09:31:30 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 09:36:46 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

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
