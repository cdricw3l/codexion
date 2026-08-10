/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_pthread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:24:13 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 16:10:25 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

pthread_t	*init_threads(int nb)
{
	pthread_t	*thrd_coder;

	thrd_coder = malloc(sizeof(pthread_t) * nb);
	if (!thrd_coder)
		return (NULL);
	return (thrd_coder);
}

clock_t	*init_clock(int nb)
{
	clock_t	*timestamps;

	timestamps = malloc(sizeof(clock_t) * nb);
	if (!timestamps)
		return (NULL);
	memset(timestamps, 0, sizeof(clock_t) * nb);
	return (timestamps);
}

pthread_mutex_t	*init_mutex(int nb)
{
	pthread_mutex_t	*mu;
	int				i;
	int				j;

	mu = malloc(sizeof(pthread_mutex_t) * nb);
	if (!mu)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&mu[i], NULL))
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&mu[j++]);
			free(mu);
			return (NULL);
		}
		i++;
	}
	return (mu);
}

pthread_cond_t	*init_cond(int nb)
{
	pthread_cond_t	*cond;
	int				i;
	int				j;

	cond = malloc(sizeof(pthread_cond_t) * nb);
	if (!cond)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (pthread_cond_init(&cond[i], NULL))
		{
			j = 0;
			while (j < i)
				pthread_cond_destroy(&cond[j++]);
			free(cond);
			return (NULL);
		}
		i++;
	}
	return (cond);
}
