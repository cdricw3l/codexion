// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   assert_thread_coder.c                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/07/31 16:16:36 by cebouhad          #+#    #+#             */
// /*   Updated: 2026/08/05 00:50:18 by cebouhad         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "assert.h"


// int launch_coder_assert(t_coder *coders, int nb_coder, t_monitoring *monitor)
// {
//     int         i;
//     pthread_t   *thread;
//     timespec_t  now;

//     thread = malloc(sizeof(pthread_t) * nb_coder);
//     assert(thread);
//     i = 0;
//     clock_gettime(CLOCK_MONOTONIC, &now);
//     while (i < nb_coder)
//     {
//         coders[i].start = now;
//         assert(*(coders[i].last_compilation) == -1);
//         pthread_create(&thread[i], NULL, thread_coders_assert, &coders[i]);
//         //usleep(50000);
//         i++;
//     }
//     i = 0;
//     while (i < nb_coder)
//         pthread_join(thread[i++], NULL);
//     free(thread);
//     return (TRUE);
    
// }

// int thread_coders_assert(void)
// {
//     START_TEST(__func__);
//     int 			params[8];
// 	t_coder			*coders;
// 	t_global_mutex	global_mu;
// 	t_monitoring	monitoring;
// 	t_queue			*request_queue;
    
//     assert(set_params(params));
//     display_params(params);
//     if(!mutex_initialisation(params[number_of_coders], &global_mu))
// 		return (write(STDERR_FILENO, "Error initialisation mutex\n", strlen("Error initialisation mutex\n")));
	
// 	//display_mutex_data(params[number_of_coders], global_mu);
// 	request_queue = queue_initialisation(params[scheduler]);
//     assert(request_queue);
// 	if (!request_queue)
// 		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
// 	coders = coders_initialisation((int *)params, &global_mu, request_queue);
// 	assert(coders);
//     if (!coders)
// 	{
// 		clean_queue(request_queue);
// 		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
// 	}
//     if (!monitoring_initialisation(params, &monitoring , &global_mu, coders))
// 		return (mutex_destroy(params[number_of_coders], &global_mu));
//     launch_coder_assert(coders, params[number_of_coders], &monitoring);
//     clean_queue(request_queue);
//     clean_memory(params[number_of_coders], &global_mu, &monitoring);
//     free(coders);

//     END_TEST(__func__);
//     return (TRUE);
// }
