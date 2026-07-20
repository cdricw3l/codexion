/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:57:35 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 23:07:16 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int init_monitoring(t_monitoring  *monitoring, t_params params, t_global_mutex *gmu)
{
    monitoring->nb_coder = params.coder;
    monitoring->ttb = params.ttb;
    monitoring->timestamp_data = gmu->timestamp_data;
    monitoring->timestamp_f = &gmu->timestamp_f;
    monitoring->timestamps_arr = malloc(sizeof(clock_t) * params.coder);
    if(!monitoring->timestamps_arr)
        return (FALSE);
    return (TRUE);
}