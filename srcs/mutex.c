/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 08:51:02 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 08:55:12 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int mutex_destroy(int nb_coder, t_global_mutex *global_mu)
{
    int i;

    pthread_mutex_destroy(&global_mu->display_f);
    pthread_mutex_destroy(&global_mu->timestamp_f);
    i = 0;
    while (i < nb_coder)
        pthread_mutex_destroy(&global_mu->dongles[i++]);
    free(global_mu->dongles);
    return (TRUE);    
}

int mutex_initialisation(int nb_coder, t_global_mutex *global_mu)
{
	int	i;

	global_mu->dongles = malloc(sizeof(pthread_mutex_t) * nb_coder);
	if(!global_mu->dongles)
		return (FALSE);
	i = 0;
	while (i < nb_coder)
	{
		global_mu->dongles[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER; 
		i++;
	}
	global_mu->display_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	global_mu->timestamp_f = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (TRUE);
}