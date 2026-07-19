/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 08:09:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/19 08:49:20 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *destroy_coders(t_coder ***coders, int idx)
{
    t_coder **c;
    int i;

    c = *coders;
    i = 0;
    while (i <= idx)
        free(c[i++]);
    free(*coders);
    return (NULL);
}

t_coder **init_coder(t_params *params, mutex_t *dongles, mutex_t *dashboard_mu, time_t *dashboard)
{
    size_t  i;
    t_coder **coders;
    t_coder *coder;
    i = 0;
    coders = malloc(sizeof(t_coder *) * (params->coder + 1));
    if (!coders)
        return (NULL);
    while (i < params->coder)
    {
        coder = malloc(sizeof(t_coder));
        if (!coder)
            return (destroy_coders(&coders, i));
        coder->id = i;
        coder->dongle_l = &dongles[get_dongle(i, params->coder, LEFT)];
        coder->dongle_r = &dongles[get_dongle(i, params->coder, RIGHT)];
        coder->mutex_dashboard = &dashboard_mu[i];
        coder->compilation_dashboard = &dashboard[i];
        /* give a copy of param to each coder avoid to use mutex for read param value */
        ft_memcopy(params, &coder->params, sizeof(t_params));
        coders[i] = coder;
        i++;
    }
    coders[i] = NULL;
    display_coders(coders);
    return (coders);
}
