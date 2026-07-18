/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/18 09:11:40 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

mutex *mutex_initialisation(size_t nb_coder)
{
    size_t i;
    char *msg;
    mutex *dongles;
    
    dongles = malloc(sizeof(mutex) * nb_coder);
    if(!dongles)
        return (NULL);
    i = 0;
    /* pthread_mutex_init return always zero. see man */
    while(i < nb_coder)
        pthread_mutex_init(&dongles[i++], NULL);
    msg = HGRN"Mutex initialised, usb are ready tu use !\n"CRESET;
    write(STDOUT_FILENO, msg, strlen(msg));
    return (dongles);
}



void *coder_thread(void *data)
{
    t_coder *coder;
    
    coder = (t_coder *)data;
    while (coder->param.ncr > 0)
    {
        pthread_mutex_lock(coder->dongle_l);
        pthread_mutex_lock(coder->dongle_r);
        update_timestamps(coder->last_compile);
        safe_print(*coder, TAKE);
        safe_print(*coder, COMPILE);
        /* compiling */
        usleep(coder->param.ttc * 1000);
        pthread_mutex_unlock(coder->dongle_l);
        pthread_mutex_unlock(coder->dongle_r);
        /* debbuging */
        safe_print(*coder, DEBBUG);
        usleep(coder->param.ttd * 1000);
        safe_print(*coder, REFACTO);
        usleep(coder->param.ttr * 1000);

        coder->param.ncr--;
    }
    return (NULL);
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
    int *dashboard;

    i = 0;
    coders = malloc(sizeof(t_coder *) * (params->coder + 1));
    if (!coders)
        return (NULL);
    dashboard = malloc(sizeof(int) * (params->coder));
    if (!dashboard)
    {
        free(coders);
        return (NULL);
    }
    while (i < params->coder)
    {
        coder = malloc(sizeof(t_coder));
        if (!coder)
            return (destroy_coders(&coders, i));
        coder->id = i;
        dashboard[i] = 0;
        coder->last_compile = &dashboard[i];
        coder->dongle_l = &dongles[get_dongle(i, params->coder, LEFT)];
        coder->dongle_r = &dongles[get_dongle(i, params->coder, RIGHT)];
        ft_memcopy(params, &coder->param, sizeof(t_params));
        coders[i] = coder;
        i++;
    }
    coders[i] = NULL;
    display_coders(coders);
    return (coders);
}

int thead_luncher(t_params *param, mutex **dongles)
{

    size_t      i;
    pthread_t   thread[CODER_MAX];
    t_coder     **coders;

    coders = init_coder(param, *dongles);
    if(!coders)
        return (FALSE);
    i = 0; 
    while (i < param->coder)
    {

        pthread_create(&thread[i], NULL, coder_thread, coders[i]);
        usleep(10);
        i++;
    }
    i = 0;
    while(i < param->coder)
    {
        pthread_join(thread[i], NULL);
        free(coders[i]);
        i++;
    }
    free(coders[i]);
    free(coders);
    return (TRUE);
}
