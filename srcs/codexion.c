/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 20:12:46 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS TRUE

int destroy_mutex(mutex_t *mu, int idx)
{
    int i;
    i = 0;

    while (i < idx)
        pthread_mutex_destroy(&mu[i++]);
    free(mu);
    return (TRUE);    
}

int main(int argc, char **argv)
{
    (void) argc;

    t_params    params;
    mutex_t     *dongles;
    mutex_t     *dashboard;


    if(parse_arguments(&argv[1], &params) == FALSE)
        return (1);
    if (DISPLAY_PARAMS)
        display_params(params);
    dongles =  mutex_initialisation(params.coder);
    if(!dongles)
        return (write(STDERR_FILENO, "Mutex dongle initialisation error\n", strlen("Mutex dongle initialisation error\n")));
    dashboard = mutex_initialisation(params.coder);
    if(!dashboard)
    {
        write(STDERR_FILENO, "Mutex dongle initialisation error\n", strlen("Mutex dongle initialisation error\n"));
        return destroy_mutex(dongles, params.coder);
    }
    thead_luncher(&params, dongles, dashboard);
    destroy_mutex(dongles, params.coder);
    destroy_mutex(dashboard, params.coder);
    return (0);
}

