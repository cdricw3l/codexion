/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 22:48:16 by cebouhad         ###   ########.fr       */
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
    display_mutex_data(global_mu, params.coder);
    clean_gmutex(&global_mu, params.coder);
    return (0);
}

