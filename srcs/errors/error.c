/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:19:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 04:25:38 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	error_msg(int code, char *arg)
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
	if (code == MUTEX_ERR)
		write(STDERR_FILENO, "Error init mutex\n", strlen("Error init mutex\n"));
	if (code == THREAD_CREATION_ERR)
		write(STDERR_FILENO, "Thread_error\n", strlen("Thread_error\n"));
	if (code == THREAD_JOINT_ERR)
		write(STDERR_FILENO, "Thread_error\n", strlen("Thread_error\n"));
	return (FALSE);
}

void *queue_err(int code)
{
	if (code == QUEUE_ERR)
		write(STDERR_FILENO, "Error init queue\n", strlen("Error init queue\n"));
	return (NULL);
}
