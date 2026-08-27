/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:27:10 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/28 01:11:46 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

#define CHECK_SIMULATION TRUE
#define DISPLAY_PARAM FALSE
#define DISPLAY_DONGLES TRUE




int main(int argc, char **argv)
{

    t_simulation        sim;
    int                 params[PARAMS_SIZE];
    
    if(!parse_arguments(&argv[1], params))
        return (write(STDERR_FILENO, "Error parsinfg arguments\n", strlen("Error parsinfg arguments\n")));
    if (DISPLAY_PARAM)
        display_params(params, argc - 1);
    if (!init_simulation(params, &sim))
    {
        write(STDERR_FILENO, "Error initialisation simulation\n", strlen("Error initialisation simulation\n"));
        return(1);
    }
    if (DISPLAY_DONGLES)
        display_dongles_data(sim.dongles, params[number_of_coders]);

    clean_simulation(&sim, TRUE);
    return (0);
}