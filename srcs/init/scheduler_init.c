/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:44:35 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 19:25:50 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void *clean_schedul(t_scheduler **schedul, int idx)
{
    int i;
    t_scheduler *data;
    data = *schedul;
    i = 0;
    while (i < idx)
    {
        pthread_mutex_destroy(&data->can_compile_mu[i]);
        pthread_cond_destroy(&data->can_compile_co[i]);
        i++;
    }
    free(data->can_compile_co);
    free(data->can_compile_mu);
    free(data);
    return (NULL);
}

t_scheduler *scheduler_init(int nb_coder, t_queue *queue)
{
	t_scheduler	*schedul;
	int 		i;

	schedul =  malloc(sizeof(t_scheduler));
	if (!schedul)
		return (NULL);
	schedul->queue = queue;
	schedul->nb_coder = nb_coder;
	schedul->can_compile = malloc(sizeof(int) * nb_coder);
	if(!schedul->can_compile)
	{
		free(schedul);
		return(NULL);
	}
	schedul->can_compile_co =  malloc(sizeof(pthread_cond_t) * nb_coder);
	if (!schedul->can_compile_co)
	{
		free(schedul->can_compile);
		free(schedul);
		return (NULL);
	}
	schedul->can_compile_mu  = malloc(sizeof(pthread_mutex_t) * nb_coder);
	if (!schedul->can_compile_mu)
	{
		free(schedul->can_compile);
		free(schedul);
		return (NULL);
	}
	i = 0;
	while (i < nb_coder)
	{
		if (pthread_cond_init(&(schedul->can_compile_co[i]), NULL))
			return (clean_schedul(&schedul, i));
        if(pthread_mutex_init(&schedul->can_compile_mu[i], NULL))
            return (clean_schedul(&schedul, i));
		schedul->can_compile[i] = FALSE;
        i++;
	}
	schedul->on_off = ON;
	return (schedul);
}
