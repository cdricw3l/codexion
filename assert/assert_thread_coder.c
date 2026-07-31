/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread_coder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:16:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/01 00:20:15 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

#define NB_REQUEST 2
#define NB_CODER 2

int set_params(int *params)
{
    params[number_of_coders] = NB_CODER;
    params[time_to_burnout] = 400;
    params[time_to_compile] = 200;
    params[time_to_debug] = 100;
    params[time_to_refactor] = 100;
    params[number_of_compiles_required] = 10;
    params[dongle_cooldown] = 10;
    params[scheduler] = FIFO ;
    return (TRUE);
}

int thread_coders_assert(void)
{
    START_TEST(__func__);
    int 			params[8];
	t_coder			*coders;
	t_global_mutex	global_mu;
	t_monitoring	monitoring;
	t_queue			*request_queue;
    
    assert(set_params(params));
    display_params(params);
    if(!mutex_initialisation(params[number_of_coders], &global_mu))
		return (write(STDERR_FILENO, "Error initialisation mutex\n", strlen("Error initialisation mutex\n")));
	
	display_mutex_data(params[number_of_coders], global_mu);
	if (!monitoring_initialisation(params[number_of_coders], &monitoring , &global_mu))
		return (mutex_destroy(params[number_of_coders], &global_mu));
	request_queue = queue_initialisation();
    assert(request_queue);
	if (!request_queue)
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	coders = coders_initialisation((int *)params, &global_mu, &monitoring, request_queue);
	assert(coders);
    if (!coders)
	{
		clean_queue(request_queue);
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	}
	display_coders(coders, params[number_of_coders]);
    clean_memory(params[number_of_coders], &global_mu, &monitoring);
    clean_queue(request_queue);
    free(coders);
    END_TEST(__func__);
    return (TRUE);
}

