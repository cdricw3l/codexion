/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:19:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/10 12:49:52 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

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


static char *get_error_msg(int code)
{
    if (code == CODER)
        return ("Error initialisation thread coders\n");
    if (code == TIMESTAMPS)
        return ("Error initialisation timestamps\n");
    if (code == TIMESTAMPS_MUTEX)
        return ("Error initialisation timestamps mutext\n");
    if (code == CODER_MUTEX)
        return ("Error initialisation coder mutext\n");
    if (code == CODER_COND)
        return ("Error initialisation coder cond\n");
    return ("");
}

int msg_error(int code)
{
    char *e_msg;

    e_msg = get_error_msg(code);
    write(STDERR_FILENO, e_msg, strlen(e_msg));
        
    return (1);
}