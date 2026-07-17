/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 11:55:01 by cebouhad         ###   ########.fr       */
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

void *destroy_coders(t_coder ***coders, int idx)
{
    t_coder **c;
    int i;

    c = *coders;
    i = 0;
    while (i <= idx)
        free(c[i++]);
    free(*coders);
    return (NULL);
}

t_coder **init_coder(t_params *params, mutex *dongles)
{
    size_t  i;
    t_coder **coders;
    t_coder *coder;

    i = 0;
    coders = malloc(sizeof(t_coder *) * (params->coder + 1));
    if (!coders)
        return (NULL);
    while (i < params->coder)
    {
        coder = malloc(sizeof(t_coder));
        if (!coder)
            return (destroy_coders(&coders, i));
        coder->id = i;
        coder->dongle_l = dongles[get_dongle(i, params->coder, LEFT, dongles)];
        coder->dongle_l = dongles[get_dongle(i, params->coder, RIGHT, dongles)];
        coder->param = *params;
        coders[i] = coder;
        i++;
    }
    coders[i] = NULL;
    display_coders(coders);
    return (coders);
}

int thead_luncher(t_params *param, mutex *dongles)
{

    size_t      i;
    pthread_t   thread[CODER_MAX];
    t_coder     **coders;

    coders = init_coder(param, dongles);
    if(!coders)
        return (FALSE);
    i = 0; 
    while (i < param->coder)
    {

        printf("coder %zu started \n", i);
        pthread_create(&thread[i], NULL, coder_thread, coders[i]);
        usleep(200);
        i++;
    }
    i = 0;
    while(i < param->coder)
    {
        pthread_join(thread[i], NULL);
        free(coders[i]);
        printf("Fin du thread %zu\n", i);
        i++;
    }
    free(coders[i]);
    free(coders);
    return (TRUE);
}
