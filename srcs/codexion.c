/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/27 08:27:11 by cebouhad         ###   ########.fr       */
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

    int params[8];
    t_global_mutex g_mutex;

    if(parse_arguments(&argv[1], params) == FALSE)
        return (1);
    if (DISPLAY_PARAMS)
        display_params(params);
    if (!g_mutex_initialisation(&g_mutex, params[number_of_coders]))
        return (FALSE);
    display_mutex_data(g_mutex, params[number_of_coders]);
    
    return (0);
}

