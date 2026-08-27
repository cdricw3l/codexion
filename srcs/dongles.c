/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:44:46 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/28 01:28:01 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	clean_queue(t_requests **queue)
{
	int i;

	i = 0;
	while (queue[i])
		free(queue[i++]);
	free(queue);
	return (TRUE);
}

void	*clean_dongles(t_dongle *dongles, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		clean_queue(dongles[i].queue);
		pthread_mutex_destroy(&dongles[i].mu_dongle);
		pthread_mutex_destroy(&dongles[i].mu_queue);
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
		if (pthread_mutex_init(&dongles[i].mu_dongle, NULL)
			|| pthread_mutex_init(&dongles[i].mu_dongle, NULL))
			return (clean_dongles(dongles, i));
		dongles[i].dongle_id= i;
		dongles[i].last_use = 0;
		dongles[i].queue = malloc(sizeof(t_requests *));
		if (!dongles[i].queue)
		{
			write(STDERR_FILENO, "Error initialisation queue\n",
				strlen("Error initialisation queue\n"));
			pthread_mutex_destroy(&dongles[i].mu_dongle);
			pthread_mutex_destroy(&dongles[i].mu_queue);
			return (clean_dongles(dongles, i));
		}
		*(dongles[i].queue) = NULL;
		dongles[i].queue_size = 0;
		i++;
	}
	return (dongles);
}
