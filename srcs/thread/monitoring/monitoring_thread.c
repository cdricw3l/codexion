/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:08:49 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 17:58:43 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

static int	check_timestamp(t_coder *coder, clock_t last_c, int *params)
{
	int			diff;
	t_timespec	now;
	clock_t		now_in_nano;

	clock_gettime(CLOCK_MONOTONIC, &now);
	now_in_nano = (now.tv_nsec + second_to_nano(now.tv_sec));
	diff = nano_to_ms(now_in_nano - last_c);
	if (diff - params[time_to_compile] > params[time_to_burnout] && \
		coder->nb_of_compil > 0 && \
		coder->nb_of_compil < params[number_of_compiles_required])
		return (FALSE);
	return (TRUE);
}

static int	check_end(t_coder *coder)
{
	int	i;
	int	check;
	int	compilation_nedeed;
	int	nb_coder;

	i = 0;
	check = 0;
	compilation_nedeed = coder[0].params[number_of_compiles_required];
	nb_coder = coder[0].params[nbc];
	while (i < nb_coder)
		if (coder[i++].nb_of_compil == compilation_nedeed)
			check++;
	if (check == nb_coder)
		return (TRUE);
	return (FALSE);
}

static	void	*set_coder_off(t_monitoring *monitor)
{
	int	j;

	j = 0;
	while (j < monitor->nb_coder)
	{
		pthread_mutex_lock(&monitor->state[j]);
		monitor->coder[j].state = FALSE;
		pthread_mutex_unlock(&monitor->state[j]);
		j++;
	}
	return (NULL);
}

static	void	*set_coder_on(t_monitoring *monitor)
{
	int			j;
	t_timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	j = 0;
	while (j < monitor->nb_coder)
	{
		pthread_mutex_lock(&monitor->state[j]);
		monitor->coder[j].start = now;
		monitor->coder[j].state = TRUE;
		pthread_mutex_unlock(&monitor->state[j]);
		j++;
	}
	return (NULL);
}

void	*monitor_routine(void *data)
{
	int				i;
	t_monitoring	*monitor;

	monitor = (t_monitoring *)data;
	i = 0;
	set_coder_on(monitor);
	while (1)
	{
		i = 0;
		pthread_mutex_lock(monitor->timestamp_f);
		while (i < monitor->nb_coder)
		{
			if (!check_timestamp(&monitor->coder[i],
					monitor->last_compilations[i], monitor->params))
			{
				safe_print(monitor->coder[i], DEAD, monitor->display_f);
				return (set_coder_off(monitor));
			}
			i++;
			pthread_mutex_unlock(monitor->display_f);
		}
		pthread_mutex_unlock(monitor->timestamp_f);
		if (check_end(monitor->coder))
			break ;
	}
	return (NULL);
}
