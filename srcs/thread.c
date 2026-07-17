/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 09:52:10 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *coder_thread(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    printf(HCYN"i'm the coder number %d\n"CRESET, coder->id);
    return (NULL);
}

int get_dongle(int id, int number_of_coder, int type, mutex *dongles)
{
    if (type == RIGHT)
    {
        if (id == number_of_coder - 1)
            return (0);
        else
            return (id + 1);
    }
    if (type == LEFT)
    {
        if (id == 0)
            return (number_of_coder - 1);
        else
            return (id - 1);
    }
    return (-1);
}

t_coder *init_coder(t_params *params, mutex *dongles)
{
    size_t  i;
    t_coder *coder;

    i = 0;
    coder = malloc(sizeof(t_coder) * params->coder);
    if (!coder)
        return (NULL);
    while (i < params->coder)
    {
        coder[i].id = i;
        coder[i].dongle_l = dongles[get_dongle(i, params->coder, LEFT, dongles)];
        coder[i].dongle_l = dongles[get_dongle(i, params->coder, RIGHT, dongles)];
        coder[i].param = *params;
        i++;
    }
    return (coder);
}

int thead_luncher(t_params *param, mutex *dongles)
{

    size_t i;
    pthread_t   thread[CODER_MAX];
    t_coder     *coders;

    
    coders = init_coder(param, dongles);
    if(!coders)
        return (NULL);
    i = 0; 
    while (i < param->coder)
    {
        
        pthread_create(&thread[i], NULL, coder_thread, &coders[i]);
        
        printf("coder %d started \n", i);
        usleep(200);
        i++;
    }
    
    i = 0;
    while(i < param->coder)
    {
        pthread_join(thread[i++], NULL);
        printf("Fin du thread %zu\n", i);
        free(dongles);
        free(coders);
    }   
    return (TRUE);
}
