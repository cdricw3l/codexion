/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 10:07:23 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS 	TRUE
#define DISPLAY_MUTEX 	FALSE


t_coder *coders_initialisation(int param[8], t_global_mutex *global_mu, t_monitoring *monitor)
{
	t_coder *coders;
	t_request *request_q;
	int 	i;

	assert(param[number_of_coders] == 20);
	request_q = malloc(sizeof(t_request) * param[number_of_coders]);
	if(!request_q)
		return (NULL);
	coders = malloc(sizeof(t_coder) * param[number_of_coders]);
	if (!coders)
	{
		free(request_q);
		return (NULL);
	}
	i = 0;
	while (i < param[number_of_coders])
	{
		coders[i].id = i + 1;
		ft_memcopy(&param, &coders[i].params, sizeof(int) * 8);
		//display_params(coders[i].params);
		printf("voici i %d and %p\n", i, &coders->coder_mutex->display_f);
		coders[i].coder_mutex->display_f = &global_mu->display_f;
		coders[i].coder_mutex->timestamp_f = &global_mu->timestamp_f;
		coders[i].coder_mutex->dongle_l = &global_mu->dongles[get_dongle(i, param[number_of_coders], LEFT)]; 
		coders[i].coder_mutex->dongle_r = &global_mu->dongles[get_dongle(i, param[number_of_coders], RIGHT)];
		coders[i].last_compilation = &monitor->last_compilations[i];
		coders[i].cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
		coders[i].requests = request_q;
	}
	return (coders);
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
	coders = coders_initialisation(params, &global_mu, &monitoring);
	if (!coders)
		return (clean_memory(params[number_of_coders], &global_mu, &monitoring));
	clean_memory(params[number_of_coders], &global_mu, &monitoring);
	return (0);
}

