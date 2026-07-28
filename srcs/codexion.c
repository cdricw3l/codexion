/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 09:07:05 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS 	TRUE
#define DISPLAY_MUTEX 	FALSE

int monitoring_initialisation(int nb_coder, t_monitoring *monitoring, t_global_mutex *global_mu)
{
	monitoring->last_compilations = malloc(sizeof(clock_t) * nb_coder);
	if(!monitoring->last_compilations)
		return (FALSE);
	memset(monitoring->last_compilations, 0, sizeof(clock_t) * nb_coder);
	monitoring->display_f =  &global_mu->display_f;
	monitoring->timestamp_f = &global_mu->timestamp_f;
	return (TRUE);
}

int main(int argc, char **argv)
{
	(void) argc;

	int params[8];
	t_coder *coders;
	t_global_mutex global_mu;
	t_monitoring monitoring;

	if(parse_arguments(&argv[1], params) == FALSE)
		return (1);
	if (DISPLAY_PARAMS)
		display_params(params);
	if(!mutex_initialisation(params[number_of_coders], &global_mu))
		return (write(STDERR_FILENO, "Error initialisation mutex\n", strlen("Error initialisation mutex\n")));
	if (DISPLAY_MUTEX)
		display_mutex_data(params[number_of_coders], global_mu);
	if (!monitoring_initialisation(params[number_of_coders], &monitoring , &global_mu))
		return (mutex_destroy(params[number_of_coders], &global_mu));
	
	mutex_destroy(params[number_of_coders], &global_mu);
	free(monitoring.last_compilations);
	return (0);
}

