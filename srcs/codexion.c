/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/21 09:14:15 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS TRUE

int destroy_mutex(t_mutex *mu, int idx)
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

    t_params        params;
    t_global_mutex  global_mu;
    t_monitoring    monitoring;
    t_coder         *coders;

    memset(&params, 0, sizeof(t_params));
    memset(&global_mu, 0, sizeof(t_global_mutex));
    if(parse_arguments(&argv[1], &params) == FALSE)
        return (1);
    if (DISPLAY_PARAMS)
        display_params(params);
    if(!g_mutex_initialisation(&global_mu, params.coder))
    {
        write(STDERR_FILENO, "Global mutex initialisation error\n", strlen("Global mutex initialisation error\n"));
        return (1);
    }
    if(!init_monitoring(&monitoring, params, &global_mu))
    {
        clean_gmutex(&global_mu, params.coder);
        write(STDERR_FILENO, "Monitoring structure initialisation error\n", strlen("Monitoring structure initialisation error\n"));
        return (1);
    }
    coders = init_coders(&params, &global_mu, &monitoring);
    if(!coders)
    {
        clean_gmutex(&global_mu, params.coder);
        write(STDERR_FILENO, "Coders structure initialisation error\n", strlen("Coders structure initialisation error\n"));
        return (1);
    }

    thead_luncher(&params, coders, &monitoring);
    clean_gmutex(&global_mu, params.coder);
    free(monitoring.timestamps_arr);
    destroy_coders(&coders, params.coder);
    return (0);
}

