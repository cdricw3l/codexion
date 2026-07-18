/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 21:21:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/18 21:22:01 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


mutex_t *mutex_initialisation(size_t nb_coder)
{
    size_t i;
    mutex_t *mutex_arr;
    
    mutex_arr = malloc(sizeof(mutex_t) * nb_coder);
    if(!mutex_arr)
        return (NULL);
    i = 0;
    /* pthread_mutex_init return always zero. see man */
    while(i < nb_coder)
        pthread_mutex_init(&mutex_arr[i++], NULL);
    // msg = HGRN"Mutex initialised, usb are ready tu use !\n"CRESET;
    // write(STDOUT_FILENO, msg, strlen(msg));
    return (mutex_arr);
}