/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 08:09:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/21 00:31:48 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *destroy_coders(t_coder **coders, int idx)
{
    int i;

    i = 0;
    while (i < idx)
    {
        free(coders[i]->coder_mutex);
        i++;
    }
    free(*coders);
    return (NULL);
}


t_coder_mutex *get_coder_mutex( t_global_mutex *gmu, size_t id, size_t total_coders)
{
    t_coder_mutex *cmu;

    cmu = malloc(sizeof(t_coder_mutex));
    if (!cmu)
        return(NULL);
    cmu->display_f = &(gmu->display_f);
    cmu->dongles_l = &(gmu->dongles[get_dongle(id, total_coders, LEFT)]);
    cmu->dongles_r = &(gmu->dongles[get_dongle(id, total_coders, RIGHT)]);
    cmu->m_timestamp_f = &(gmu->timestamp_f);
    cmu->m_timestamp_data = &(gmu->timestamp_data[id]);
    return (cmu);
}

t_coder *init_coders(t_params *params, t_global_mutex *gmu, t_monitoring *monitoring)
{

    size_t  i;
    t_coder_mutex cmu;
    t_coder *coders;

    coders = malloc(sizeof(t_coder) * (params->coder));
    if(!coders)
        return (NULL);
    i = 0;
    while (i < params->coder)
    {   
        coders[i].id = i + 1;
        coders[i].timestamps = &(monitoring->timestamps_arr[i]);
        coders[i].coder_mutex = get_coder_mutex(gmu, i, params->coder);
        if(!coders[i].coder_mutex)
        {
            write(STDERR_FILENO, "Coders mutex initialisation error\n", strlen("Coders mutex initialisation error\n"));
            return (destroy_coders(&coders, i));
        }
        ft_memcopy(params, &coders[i].params, sizeof(t_params));
        i++;
    }
    return (coders);
}
