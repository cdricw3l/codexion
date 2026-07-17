/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 08:45:10 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS TRUE


int mutex_initialisation(mutex dongles[CODER_MAX], size_t nb_coder)
{
    size_t i;

    i = 0;
    /* pthread_mutex_init return always zero. see man */
    while(i < nb_coder)
        pthread_mutex_init(&dongles[i++], NULL);
    write(STDOUT_FILENO, "Mutex initialised, usb are ready\n", strlen("Mutex initialised, usb are ready\n"));
    return (TRUE);
}

int main(int argc, char **argv)
{
    (void) argc;

    t_params params;
    pthread_mutex_t dongles[CODER_MAX];


    if(parse_arguments(&argv[1], &params) == FALSE)
        return (1);
    if (DISPLAY_PARAMS)
        display_params(params);
    mutex_initialisation(dongles, params.coder);

    thead_luncher(&params, dongles);
    return (0);
}