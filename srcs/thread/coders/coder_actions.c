/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 21:41:48 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 02:53:09 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

static void	lock_dongle(t_coder *coder)
{
	if (coder->id == 1 || coder->id == coder->params[nbc])
	{
		pthread_mutex_lock(coder->coder_mutex.dongle_r.dongle);
		pthread_mutex_lock(coder->coder_mutex.dongle_l.dongle);
	}
	else
	{
		pthread_mutex_lock(coder->coder_mutex.dongle_l.dongle);
		pthread_mutex_lock(coder->coder_mutex.dongle_r.dongle);
	}
}

static void	unlock_dongle(t_coder *coder)
{
	if (coder->id == 1 || coder->id == coder->params[nbc])
	{
		if (coder->state)
		{
			pthread_mutex_unlock(coder->coder_mutex.dongle_r.dongle);
			pthread_mutex_unlock(coder->coder_mutex.dongle_l.dongle);
		}
	}
	else
	{
		if (coder->state)
		{
			pthread_mutex_unlock(coder->coder_mutex.dongle_l.dongle);
			pthread_mutex_unlock(coder->coder_mutex.dongle_r.dongle);
		}
	}
}

void	compile(t_coder *coder)
{
	lock_dongle(coder);
	safe_print(*coder, TAKE, coder->coder_mutex.display_f);
	safe_print(*coder, COMPILE, coder->coder_mutex.display_f);
	set_timestamp(coder, TIMESTAMP_COMPILATION);
	usleep(coder->params[time_to_compile] * 1000);
	unlock_dongle(coder);
	set_timestamp(coder, TIMESTAMP_DONGLE);
}

void	debbug(t_coder *coder)
{
	safe_print(*coder, DEBBUG, coder->coder_mutex.display_f);
	usleep(coder->params[time_to_debug] * 1000);
}

void	refactor(t_coder *coder)
{
	safe_print(*coder, REFACTO, coder->coder_mutex.display_f);
	usleep(coder->params[time_to_refactor] * 1000);
}
