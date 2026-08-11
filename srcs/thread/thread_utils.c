/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:41:52 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/11 12:23:36 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int check_simulation_state(t_sim *sim)
{
    int is_runing;

    is_runing = TRUE;
    pthread_mutex_lock(&sim->simulation_mu);
    if (sim->simulation_state == OFF)
        is_runing = FALSE;
    pthread_mutex_unlock(&sim->simulation_mu);
    return (is_runing);
}

int get_param(t_sim *sim, int param)
{
    int value;
    if (param < 0 || param > PARAMS_SIZE)
        return (-1);
    pthread_mutex_lock(&sim->param_mu);
    value = sim->params[param];
    pthread_mutex_unlock(&sim->param_mu);
    return (value);
}