/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:09:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 15:26:18 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static int	launch_coders(t_coder *coders,
	t_monitoring *monitor, int nb_coder, pthread_t *thread_coder)
{
	int			i;

	i = 0;
	while (i < nb_coder)
	{
		coders[i].last_compilation = &monitor->last_compilations[i];
		coders[i].state = FALSE;
		if (pthread_create(&thread_coder[i], NULL, coder_routine, &coders[i]))
			return (error_msg(THREAD_CREATION_ERR, NULL));
		i++;
	}
	return (TRUE);
}

static int	launch_monitor(t_monitoring *monitor, pthread_t *thread_monitor)
{
	if (pthread_create(thread_monitor, NULL, monitor_routine, monitor))
		return (FALSE);
	return (TRUE);
}

static int launch_scheduler(t_scheduler *scheduler, pthread_t *thread_scheduler)
{
	if (pthread_create(thread_scheduler, NULL, scheduler_routine, scheduler))
		return (FALSE);
	return (TRUE);
}	

static void	joint_thread(pthread_t *thread_coder,
	pthread_t thread_monitor, pthread_t thread_schedule, int nb_coder)
{
	int	i;

	if (pthread_join(thread_monitor, NULL))
		error_msg(THREAD_JOINT_ERR, NULL);
	if (pthread_join(thread_schedule, NULL))
		error_msg(THREAD_JOINT_ERR, NULL);
	i = 0;
	while (i < nb_coder)
	{
		if (pthread_join(thread_coder[i], NULL))
			error_msg(THREAD_JOINT_ERR, NULL);
		i++;
	}
}

int	thread_launcher(t_scheduler *scheduler, t_coder *coders, t_monitoring *monitor, int nb_coder)
{
	pthread_t	*thread_coder;
	pthread_t	thread_monitor;
	pthread_t	thread_scheduler;

	thread_coder = malloc(sizeof(pthread_t) * nb_coder);
	if (!thread_coder)
		return (FALSE);
	if (!launch_coders(coders, monitor, nb_coder, thread_coder)
		|| !launch_monitor(monitor, &thread_monitor)
		|| !launch_scheduler(scheduler, &thread_scheduler))
	{
		free(thread_coder);
		return (FALSE);
	}
	joint_thread(thread_coder, thread_monitor, thread_scheduler,nb_coder);
	free(thread_coder);
	return (TRUE);
}
