/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 17:24:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS TRUE

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

int main(int argc, char **argv)
{
    (void) argc;

    t_params    params;
    mutex       *dongles;


    if(parse_arguments(&argv[1], &params) == FALSE)
        return (1);
    if (DISPLAY_PARAMS)
        display_params(params);
    dongles =  mutex_initialisation(params.coder);
    if(!dongles)
        return (write(STDERR_FILENO, "Mutex initialisation error\n", strlen("Mutex initialisation error\n")));
    thead_luncher(&params, &dongles);
    free(dongles);
    return (0);
}