/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:22:43 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 18:00:59 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int sim_initialisation_error(t_sim *sim, int code)
{
	int nb;

	if (sim)
		nb = sim->params[number_of_coders];
	if (sim->coder_state)
		free(sim->coder_state);
	if (sim->coders)
		free(sim->coders);
	if (sim->timestamp)
		free(sim->timestamp);
	if (sim->coder_state_mu)
		clean_dynamique_mutex(sim->timestamp_mu, nb);
	if (sim->timestamp_mu)
		clean_dynamique_mutex(sim->timestamp_mu, nb);
	if (sim->coder_mu)
		clean_dynamique_mutex(sim->coder_mu, nb);
	if (sim->coder_cond)
		clean_dynamique_cond(sim->coder_cond, nb);
	pthread_mutex_destroy(&sim->display_mu);
	msg_error(code);
	return (0);
}

int	init_sim(int *params, t_dongle *dongles, t_sim *sim)
{
	sim->params = params;
	sim->simulation_state = OFF;
	sim->coder_state = init_int_arr(params[number_of_coders]);
	if (!sim->coder_state)
		return (sim_initialisation_error(sim, STATE));
	sim->coders = init_threads(params[number_of_coders]);
	if (!sim->coders)
		return (sim_initialisation_error(sim, CODER));
	sim->timestamp = init_clock(params[number_of_coders]);
	if (!sim->timestamp)
		return (sim_initialisation_error(sim, TIMESTAMPS));
	sim->timestamp_mu = init_mutex(params[number_of_coders]);
	if (!sim->timestamp_mu)
		return (sim_initialisation_error(sim, TIMESTAMPS_MUTEX));
	sim->coder_mu = init_mutex(params[number_of_coders]);
	sim->coder_state_mu = init_mutex(params[number_of_coders]);
	if (!sim->coder_state_mu)
		return (sim_initialisation_error(sim, STATE_MUTEX));
	if (!sim->coder_mu)
		return (sim_initialisation_error(sim, CODER_MUTEX));
	sim->coder_cond = init_cond(params[number_of_coders]);
	if (!sim->coder_cond)
		return (sim_initialisation_error(sim, CODER_COND));
	sim->dongles = dongles;
	sim->display_mu = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (0);
}
