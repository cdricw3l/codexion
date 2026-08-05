/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:53:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 16:16:47 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static t_coder_mutex	get_coder_mutex(int id,
	int nb_coder, t_global_mutex *global_mu)
{
	t_dongle		left;
	t_dongle		right;
	t_coder_mutex	coder_mu;

	coder_mu.display_f = &global_mu->display_f;
	coder_mu.timestamp_f = &global_mu->timestamp_f;
	coder_mu.state = &global_mu->state[id];
	left.dongle = &global_mu->dongles[get_dongle(id, nb_coder, LEFT)];
	left.last_use = 0;
	right.dongle = &global_mu->dongles[get_dongle(id, nb_coder, RIGHT)];
	right.last_use = 0;
	coder_mu.dongle_l = left; 
	coder_mu.dongle_r = right;
	return (coder_mu);
}

t_coder	*coders_init(int *params, t_global_mutex *global_mu, t_queue *queue, t_scheduler *schedul)
{
	int		i;
	t_coder	*coders;

	coders = malloc(sizeof(t_coder) * params[nbc]);
	if (!coders)
		return (NULL);
	i = 0;
	assert(params[nbc] == 4);
	while (i < params[nbc])
	{
		coders[i].id = i + 1;
		ft_memcopy(params, coders[i].params, sizeof(int) * 8);
		coders[i].coder_mutex = get_coder_mutex(i, params[nbc], global_mu);
		coders[i].nb_of_compil = 0;
		coders[i].can_compile = &schedul->can_compile[i];
		assert(schedul->can_compile[i] == FALSE); 
		coders[i].can_compile_cond = &schedul->can_compile_co[i];
		coders[i].coder_mutex.can_compile_mu = &schedul->can_compile_mu[i];
		coders[i].queue = queue;
		i++;
	}
	return (coders);
}