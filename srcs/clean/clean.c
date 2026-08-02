/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 09:36:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/02 13:39:31 by cebouhad         ###   ########.fr       */
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
    {
        pthread_mutex_destroy(&global_mu->dongles[i]);
        pthread_mutex_destroy(&global_mu->coder_mutex[i++]);

    }
    free(global_mu->dongles);
    free(global_mu->coder_mutex);
    return (TRUE);    
}

int clean_memory(int nb_coder, t_global_mutex *global_mu, t_monitoring *monitoring)
{
	mutex_destroy(nb_coder, global_mu);
	free(monitoring->last_compilations);
	return (0);
}

int clean_queue(t_queue *queue)
{
    if(!queue)
        return (FALSE);
    free(queue->request_queue);
    free(queue);
    return (TRUE);
}