/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 11:19:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS 	TRUE
#define DISPLAY_MUTEX 	FALSE





int main(int argc, char **argv)
{
	(void) argc;

	int params[8];
	t_coder *coders;
	t_global_mutex global_mu;
	t_monitoring monitoring;
	t_request *request_queue;

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
	request_queue = queue_initialisation(params[number_of_coders]);
	if(!request_queue)
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	coders = coders_initialisation((int *)params, &global_mu, &monitoring, request_queue);
	if (!coders)
	{
		free(request_queue);
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	}


	
	free(coders);
	free(request_queue);
	clean_memory(params[number_of_coders], &global_mu, &monitoring);
	return (0);
}

