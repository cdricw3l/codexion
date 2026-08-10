/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:19:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 13:06:15 by cebouhad         ###   ########.fr       */
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

