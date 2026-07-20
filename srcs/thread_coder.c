/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_coder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 20:14:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 20:25:54 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *coder_thread(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    while (coder->params.ncr > 0)
    {
        if (coder->id == 0)
        {
            pthread_mutex_lock(coder->dongle_r);
            safe_print(*coder, TAKE);
            pthread_mutex_lock(coder->dongle_l);
            safe_print(*coder, TAKE);
        }
        else
        {
            pthread_mutex_lock(coder->dongle_l);
            safe_print(*coder, TAKE);
            pthread_mutex_lock(coder->dongle_r);
            safe_print(*coder, TAKE);
        }
        safe_print(*coder, COMPILE);
        /* compiling */
        usleep(coder->params.ttc * 1000);
        /* cooldown */
        usleep(coder->params.dc * 1000);
        pthread_mutex_unlock(coder->dongle_r);
        pthread_mutex_unlock(coder->dongle_l);
        /* debbuging */
        safe_print(*coder, DEBBUG);
        usleep(coder->params.ttd * 1000);
        safe_print(*coder, REFACTO);
        usleep(coder->params.ttr * 1000);
        coder->params.ncr--;
    }
    return (NULL);
}