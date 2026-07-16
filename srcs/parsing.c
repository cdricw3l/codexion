/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:51:42 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/16 21:31:49 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

enum e_PARSING_ERROR
{
    NB_ARG,
    BAD_ARG
};

int parsing_error_msg(int code, char *arg)
{
    char *msg;

    if (code == NB_ARG)
    {
        msg = HRED"Bad number of arguments"CRESET"\n";
        write(STDERR_FILENO, msg, strlen(msg));
    }
    if (code == BAD_ARG)
    {
        msg = HRED" is a bad argument"CRESET"\n";
        write(STDERR_FILENO, HRED, strlen(HRED));
        write(STDERR_FILENO, "'", 1);
        write(STDERR_FILENO, arg, strlen(arg));
        write(STDERR_FILENO, "'", 1);
        write(STDERR_FILENO, msg, strlen(msg));
        write(STDERR_FILENO, CRESET, strlen(CRESET));
    }
    return (FALSE);
}

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
        params->nb_philo = atoi(arg);
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