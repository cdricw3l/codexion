/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 21:21:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/27 10:03:44 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	*destroy_arr_mutex(t_mutex **mu, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
		pthread_mutex_destroy(&(*mu)[i++]);
	free(*mu);
	return (NULL);
}

static t_mutex	*get_arr_of_initialised_mutex(size_t coders)
{
	size_t	i;
	t_mutex	*arr;

	arr = malloc(sizeof(t_mutex) * coders);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < coders)
	{
		arr[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
	return (arr);
}



int	clean_gmutex(t_global_mutex *mu, size_t coders)
{

	pthread_mutex_destroy(&mu->display_f);
	pthread_mutex_destroy(&mu->timestamp_f);
	if (mu->dongles)
		destroy_arr_mutex(&mu->dongles, coders);
	if (mu->timestamp_data)
		destroy_arr_mutex(&mu->timestamp_data, coders);
	return (FALSE);
}

int	g_mutex_initialisation(t_global_mutex *gmutex, size_t coders)
{
	gmutex->display_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	gmutex->timestamp_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	gmutex->dongles = get_arr_of_initialised_mutex(coders);
	if (!gmutex->dongles)
	{
		write(STDERR_FILENO, "Error mutex dongle initialisation\n", \
			strlen("Error mutex dongle initialisation\n"));
		return (clean_gmutex(gmutex, coders));
	}
	gmutex->timestamp_data = get_arr_of_initialised_mutex(coders);
	if (!gmutex->timestamp_data)
	{
		write(STDERR_FILENO, "Error mutex dongle initialisation\n", \
			strlen("Error mutex dongle initialisation\n"));
		return (clean_gmutex(gmutex, coders));
	}
	return (TRUE);
}
