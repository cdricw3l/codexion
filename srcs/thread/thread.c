/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:09:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/03 10:00:01 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"


int thread_launcher(t_coder *coder, t_monitoring *monitor, int nb_coder)
{
    int i;
    pthread_t *threads;

    
    if(!coder || !monitor)
        return(FALSE);
    threads = malloc(sizeof(pthread_t) * nb_coder);
    if(!threads)
        return (FALSE);
    i = 0;
    
    while (i < nb_coder)
    {

        pthread_create(&threads[i], NULL, coder_routine, &coder[i]);
        sleep(1);
        i++;
    }
    i = 0;
    while (i < nb_coder)
    {
        pthread_join(threads[i], NULL);    
        i++;
    }
    return (TRUE);
}