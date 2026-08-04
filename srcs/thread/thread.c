/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:09:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/04 22:42:29 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static int	launch_coders(t_coder *coders, t_monitoring *monitor, int nb_coder, pthread_t *thread_coder)
{
	int			i;
	
	i = 0;
	while (i < nb_coder)
	{
		coders[i].last_compilation  = &monitor->last_compilations[i];
		coders[i].state = FALSE;
		if (pthread_create(&thread_coder[i], NULL, coder_routine, &coders[i]))
		{
			write(STDERR_FILENO, "Error coder thread creation\n", strlen("Error coder thread creation\n"));
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int launch_monitor(t_monitoring *monitor, pthread_t *thread_monitor)
{
	if(pthread_create(thread_monitor, NULL, monitor_routine, monitor))
		return (FALSE);
	return (TRUE);
}

static void joint_thread(pthread_t *thread_coder, pthread_t *thread_monitor, int nb_coder)
{
	int i;

	if(pthread_join(*thread_monitor, NULL))
		write(STDERR_FILENO, "Error join monitor thread\n", strlen("Error join monitor thread\n"));
	i = 0;
	while (i < nb_coder)
	{
		if(pthread_join(thread_coder[i], NULL))
			write(STDERR_FILENO, "Error join coder thread\n", strlen("Error join coder thread\n"));
		i++;
	}
}

int thread_launcher(t_coder *coders, t_monitoring *monitor, int nb_coder)
{
	pthread_t   *thread_coder;
	pthread_t   thread_monitor;

	thread_coder = malloc(sizeof(pthread_t) * nb_coder);
	if(!thread_coder)
		return(FALSE);
	if(!launch_coders(coders, monitor, nb_coder, thread_coder) || !launch_monitor(monitor, &thread_monitor))
	{
		free(thread_coder);
		return(FALSE);
	}
	joint_thread(thread_coder, &thread_monitor, nb_coder);
	free(thread_coder);
	return (TRUE);
}