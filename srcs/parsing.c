/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:51:42 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 08:21:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


int check_args(char *arg, int idx)
{
    if (idx == scheduler)
    {
        if (strcmp("fifo", arg) && strcmp("edf", arg))
            return(parsing_error_msg(BAD_ARG, arg));
    }
    else
    {
        while (*arg)
        {
            if (ft_is_digit(*arg) == FALSE)
                return (parsing_error_msg(BAD_ARG, arg));
            arg++;
        }
    }
    return (TRUE);
}

void save_param(char *arg, int idx, t_params *params)
{
    if (idx == number_of_coders)
        params->coder = atoi(arg);
    else if (idx == time_to_burnout)
        params->ttb = atoi(arg);
    else if (idx == time_to_compile)
        params->ttc = atoi(arg);
    else if (idx == time_to_debug)
        params->ttd = atoi(arg);
    else if (idx == time_to_refactor)
        params->ttr = atoi(arg);
    else if (idx == number_of_compiles_required)
        params->ncr = atoi(arg);
    else if (idx == dongle_cooldown)
        params->dc = atoi(arg);
    else if (idx == scheduler && !strcmp("fifo", arg))
        params->scheduler = FIFO;
    else if (idx == scheduler && !strcmp("edf", arg))
        params->scheduler = EDF;
}

int parse_arguments(char **args, t_params *params)
{
    int i;
    if (get_str_arr_len(args) != 8)
    {
        printf("nv arg %zu\n", get_str_arr_len(args));
        return (parsing_error_msg(NB_ARG, NULL));
    }
    i = 0;
    while (args[i])
    {
        if (check_args(args[i], i) == FALSE)
            return (FALSE);
        save_param(args[i], i, params);
        i++;
    }
    return (TRUE);
}