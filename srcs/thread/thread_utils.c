/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:41:52 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/28 01:06:19 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void set_simulation_state(t_simulation *sim, int state)
{
    if(state == TRUE || state == FALSE)
    {
        pthread_mutex_lock(&sim->sim_state_mutex);
        sim->simulation_state = state;
        pthread_mutex_unlock(&sim->sim_state_mutex);
    }
}

int check_simulation_state(t_simulation *sim, int state)
{
    int is_state;

    is_state = TRUE;
    if(state == TRUE || state == FALSE)
    {
        pthread_mutex_lock(&sim->sim_state_mutex);
        if (sim->simulation_state != state)
            is_state = FALSE;
        pthread_mutex_unlock(&sim->sim_state_mutex);
    }
    return (is_state);
}



void safe_printf(t_simulation *sim, char *msg)
{
    pthread_mutex_lock(&sim->display_mutex);
    printf("%s\n", msg);
    pthread_mutex_unlock(&sim->display_mutex);
}