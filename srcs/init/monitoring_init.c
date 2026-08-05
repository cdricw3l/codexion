/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:52:44 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 14:53:09 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_monitoring	*monitoring_init(int *params,
	t_global_mutex *global_mu, t_coder *coder)
{
	t_monitoring	*monitoring;

	monitoring = malloc(sizeof(t_monitoring));
	if (!monitoring)
		return (NULL);
	monitoring->last_compilations = malloc(sizeof(clock_t) * params[nbc]);
	if (!monitoring->last_compilations)
	{
		free(monitoring);
		return (NULL);
	}
	memset(monitoring->last_compilations, -1, sizeof(clock_t) * params[nbc]);
	monitoring->display_f = &global_mu->display_f;
	monitoring->timestamp_f = &global_mu->timestamp_f;
	monitoring->nb_coder = params[nbc];
	monitoring->coder = coder;
	ft_memcopy(params, monitoring->params, sizeof(int) * 8);
	monitoring->state = global_mu->state;
	return (monitoring);
}
