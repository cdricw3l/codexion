/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:27:10 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 10:13:18 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

#define NB_CODER 10


int main(int argc, char **argv)
{
    t_dongle *dongles;
    int params[8];
    
    if(!parse_arguments(&argv[1], params))
        return (write(STDERR_FILENO, "Error parsinfg arguments\n", strlen("Error parsinfg arguments\n")));
    display_params(params, argc - 1);
    dongles = dongles_initialisation(NB_CODER);
    if(!dongles)
    {
        write(STDERR_FILENO, "Error initialisation dongle\n", strlen("Error initialisation dongle\n"));
        return(1);
    }
    display_dongles_data(dongles, NB_CODER);
    clean_dongles(dongles, NB_CODER);
    return (0);
}