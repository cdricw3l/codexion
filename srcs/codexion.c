/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 22:51:32 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS TRUE

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