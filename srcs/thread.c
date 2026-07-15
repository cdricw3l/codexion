/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/15 18:22:37 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *coder_thread(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    printf(HCYN"i'm the coder number %d\n"CRESET, coder->id);
    return (data);
}


int thead_luncher(t_params *param)
{
    int i;
    pthread_t   thread[CODER_MAX];
    t_coder     coder[CODER_MAX];

    i = 0;
    while (i < param->nb_philo)
    {
        coder[i].id = i;
        coder[i].param = param;
        pthread_create(&thread[i], NULL, coder_thread, &coder[i]);
        usleep(200);
        i++;
    }
    i = 0;
    while(i < param->nb_philo)
        pthread_join(thread[i], NULL);

    return (TRUE);
}