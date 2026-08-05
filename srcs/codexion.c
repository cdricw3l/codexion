/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 04:16:59 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int argc, char **argv)
{
	int				params[8];
	t_coder			*coders;
	t_global_mutex	global_mu;
	t_monitoring	*monitoring;
	t_queue			*request_queue;

	if (parse_arguments(argc, &argv[1], params) == FALSE)
		return (1);
	if (!mutex_init(params[nbc], &global_mu))
		return (error_msg(MUTEX_ERR, NULL));
	request_queue = queue_init(params[scheduler], params[time_to_burnout]);
	if (!request_queue)
		return (clean(params[nbc], NULL, &global_mu, NULL));
	coders = coders_init((int *)params, &global_mu, request_queue);
	if (!coders)
		return (clean(params[nbc], NULL, &global_mu, request_queue));
	monitoring = monitoring_init((int *)params, &global_mu, coders);
	if (!monitoring)
		return (clean(params[nbc], coders, &global_mu, request_queue));
	thread_launcher(coders, monitoring, params[nbc]);
	clean(params[nbc], coders, &global_mu, request_queue);
	free(monitoring->last_compilations);
	free(monitoring);
	return (0);
}
