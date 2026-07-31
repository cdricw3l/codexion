/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 09:36:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 13:06:24 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

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

int clean_memory(int nb_coder, t_global_mutex *global_mu, t_monitoring *monitoring)
{
	mutex_destroy(nb_coder, global_mu);
	free(monitoring->last_compilations);
	return (0);
}
