/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:52:14 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 14:54:39 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

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
