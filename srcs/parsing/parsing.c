/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:51:42 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/10 19:55:30 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static int check_args(char *arg, int idx)
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

static void save_param(char *arg, int idx, int params[8])
{
    if (idx == number_of_coders)
        params[number_of_coders] = atoi(arg);
    else if (idx == time_to_burnout)
        params[time_to_burnout] = atoi(arg);
    else if (idx == time_to_compile)
        params[time_to_compile] = atoi(arg);
    else if (idx == time_to_debug)
        params[time_to_debug] = atoi(arg);
    else if (idx == time_to_refactor)
        params[time_to_refactor] = atoi(arg);
    else if (idx == number_of_compiles_required)
        params[number_of_compiles_required] = atoi(arg);
    else if (idx == dongle_cooldown)
        params[dongle_cooldown] = atoi(arg);
    else if (idx == scheduler && !strcmp("fifo", arg))
        params[scheduler] = FIFO;
    else if (idx == scheduler && !strcmp("edf", arg))
        params[scheduler] = EDF;
}

int parse_arguments(char **args, int params[8])
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
    /* check if the number of coder is less than 2*/
    if(params[number_of_coders] < 2)
        return(FALSE);
    return (TRUE);
}