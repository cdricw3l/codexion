/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:44:46 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 11:25:51 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	clean_queue(t_queue_dongle **queue)
{
	t_queue_dongle	**tmp;

	tmp = queue;
	while (*(tmp))
	{
		free(*(tmp));
		tmp++;
	}
	free(queue);
	return (TRUE);
}

void	*clean_dongles(t_dongle *dongles, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		clean_queue(dongles->queue);
		pthread_mutex_destroy(&dongles->dongle);
		i++;
	}
	free(dongles);
	return (NULL);
}

t_dongle	*dongles_initialisation(int nb_coder)
{
	int			i;
	t_dongle	*dongles;

	dongles = malloc(sizeof(t_dongle) * nb_coder);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < nb_coder)
	{
		if (pthread_mutex_init(&dongles[i].dongle, NULL)
			|| pthread_mutex_init(&dongles[i].mu_dongle, NULL))
			return (clean_dongles(dongles, i));
		dongles[i].dongle_id= i;
		dongles[i].last_use = 0;
		dongles[i].queue = malloc(sizeof(t_queue_dongle *));
		if (!dongles[i].queue)
		{
			write(STDERR_FILENO, "Error initialisation queue\n",
				strlen("Error initialisation queue\n"));
			pthread_mutex_destroy(&dongles[i].dongle);
			pthread_mutex_destroy(&dongles[i].mu_dongle);
			return (clean_dongles(dongles, i));
		}
		*(dongles[i].queue) = NULL;
		dongles[i].queue_size = 0;
		i++;
	}
	return (dongles);
}
