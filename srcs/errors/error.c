/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:19:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/13 12:28:37 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"
#define BASE_16 "0123456789ABCDEF"


void ft_putnbr_error(int fd, int nb, int base)
{
    long n;
    char c;
    
    n = nb;
    if (nb < 0)
    {
        write(fd, "-", 1);
        n = n *-1;
    }
    if (nb >= base)
        ft_putnbr_error(fd, nb / base, base);
    c =  BASE_16[nb % base];
    write(fd, &c, 1);
}

int	parsing_error_msg(int code, char *arg)
{
	char	*msg;

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

static char	*get_error_msg(int code)
{
	if (code == STATE)
		return ("Error initialisation state coders\n");
	if (code == STATE_MUTEX)
		return ("Error initialisation state mutex coders\n");
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
	if (code == COUNTER)
		return ("Error initialisation coder counter\n");
	if (code == COUNTER_MU)
		return ("Error initialisation coder counter mutex\n");
	return ("");
}

int	msg_error(int code)
{
	char	*e_msg;

	e_msg = get_error_msg(code);
	write(STDERR_FILENO, e_msg, strlen(e_msg));
	return (1);
}
