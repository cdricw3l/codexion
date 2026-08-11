/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:41:52 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/11 15:54:51 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void change_simulation_state(t_sim *sim, int state)
{
    pthread_mutex_lock(&sim->simulation_mu);
    sim->simulation_state = state;
    pthread_mutex_unlock(&sim->simulation_mu);
}

int check_simulation_state(t_sim *sim, int state)
{
    int is_state;

    is_state = TRUE;
    pthread_mutex_lock(&sim->simulation_mu);
    if (sim->simulation_state != state)
        is_state = FALSE;
    pthread_mutex_unlock(&sim->simulation_mu);
    return (is_state);
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