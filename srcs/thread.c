/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/18 00:21:52 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void safe_print(t_coder coder, int action)
{
    mutex print_mutex;

    pthread_mutex_lock(&print_mutex);
    if (action == TAKE)
        printf(HCYN"[ %d ] i'm the coder number %d, i take dongle left: %p and dongle right %p\n"CRESET,coder.param.ncr ,coder.id, coder.dongle_l, coder.dongle_r);
    if (action == RELEASE)
        printf(HYEL"[ %d ] i'm the coder number %d, i release dongle left: %p and dongle right %p\n"CRESET, coder.param.ncr ,coder.id, coder.dongle_l, coder.dongle_r);
    pthread_mutex_unlock(&print_mutex);
}

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
    while (coder->param.ncr >=0)
    {
        if (pthread_mutex_lock(coder->dongle_l) == EBUSY)
            printf("coder %d wait for dongle left %p\n", coder->id, coder->dongle_l);
        if (pthread_mutex_lock(coder->dongle_r) == EBUSY)
            printf("coder %d wait for dongle left %p\n", coder->id, coder->dongle_r);
        safe_print(*coder, TAKE);
        usleep(1000000);
        pthread_mutex_unlock(coder->dongle_l);
        pthread_mutex_unlock(coder->dongle_r);
        safe_print(*coder, RELEASE);
        coder->param.ncr--;
    }
    return (NULL);
}

int get_dongle(int id, int number_of_coder, int type)
{
    if (type == RIGHT)
        return (id);
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
        //printf("dongle left %d\nDongle right %d\n",get_dongle(i, params->coder, LEFT), get_dongle(i, params->coder, RIGHT));
        //printf("dongle left %p\nDongle right %p\n", &dongles[get_dongle(i, params->coder, LEFT)], &dongles[get_dongle(i, params->coder, RIGHT)]);
        coder->id = i;
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
