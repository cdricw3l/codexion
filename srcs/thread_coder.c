/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_coder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 20:14:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/27 10:05:27 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *coder_thread(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    while (coder->params[number_of_compiles_required] > 0)
    {
        if (coder->id == 1)
        {
            pthread_mutex_lock(coder->coder_mutex->dongles_r);
            safe_print(*coder, TAKE);
            pthread_mutex_lock(coder->coder_mutex->dongles_l);
            safe_print(*coder, TAKE);
        }
        else
        {
            pthread_mutex_lock(coder->coder_mutex->dongles_l);
            safe_print(*coder, TAKE);
            pthread_mutex_lock(coder->coder_mutex->dongles_r);
            safe_print(*coder, TAKE);
        }
        safe_print(*coder, COMPILE);
        /* compiling */
        usleep(coder->params[time_to_compile] * 1000);
        /* cooldown */
        //usleep(coder->params.dc * 1000);
        pthread_mutex_unlock(coder->coder_mutex->dongles_l);
        pthread_mutex_unlock(coder->coder_mutex->dongles_r);
        /* debbuging */
        safe_print(*coder, DEBBUG);
        usleep(coder->params[time_to_debug] * 1000);
        safe_print(*coder, REFACTO);
        usleep(coder->params[time_to_refactor] * 1000);
        coder->params[number_of_compiles_required]--;
    }
    return (NULL);
}
