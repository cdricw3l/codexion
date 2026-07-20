/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 21:21:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 22:49:10 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *destroy_arr_mutex(t_mutex **mu, size_t idx)
{
    size_t i;

    i = 0;
    while (i < idx)
        pthread_mutex_destroy(&(*mu)[i++]);
    free(*mu);
    return (NULL);
}

int clean_gmutex(t_global_mutex *mu, size_t coders)
{
    size_t i;

    pthread_mutex_destroy(&mu->display_f);
    pthread_mutex_destroy(&mu->timestamp_f);
    if (mu->dongles)
        destroy_arr_mutex(&mu->dongles, coders);
    if (mu->timestamp_data)
        destroy_arr_mutex(&mu->timestamp_data, coders);
    return (FALSE);
}

t_mutex *get_arr_of_initialised_mutex(size_t coders)
{
    t_mutex *arr;
    size_t  i;

    arr = malloc(sizeof(t_mutex) * coders);
    if (!arr)
        return (NULL);
    i = 0;
    while (i < coders)
    {
        if (pthread_mutex_init(&arr[i], NULL))
            return (destroy_arr_mutex(&arr, i));
        i++;
    }
    return (arr);
}

int mutex_initialisation(t_mutex *mu)
{
    if(pthread_mutex_init(mu, NULL))
        return (FALSE);
    return (TRUE);
}

int g_mutex_initialisation(t_global_mutex  *gmutex, size_t coders)
{
    if(!mutex_initialisation(&gmutex->display_f))
        return (clean_gmutex(gmutex, coders));
    if(!mutex_initialisation(&gmutex->timestamp_f))
        return (clean_gmutex(gmutex, coders));
    gmutex->dongles = get_arr_of_initialised_mutex(coders);
    if(!gmutex->dongles)
    {
        write(STDERR_FILENO, "Error mutex dongle initialisation\n", strlen("Error mutex dongle initialisation\n"));
        return (clean_gmutex(gmutex, coders));
    }
    gmutex->timestamp_data = NULL;
    gmutex->timestamp_data = get_arr_of_initialised_mutex(coders);
    if(!gmutex->timestamp_data)
    {
        write(STDERR_FILENO, "Error mutex dongle initialisation\n", strlen("Error mutex dongle initialisation\n"));
        return (clean_gmutex(gmutex, coders));
    }
    return (TRUE);
}   
