/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 03:28:38 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 03:30:43 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

long	second_to_nano(long sec)
{
	return (sec * 1000000000);
}

long	ms_to_nano(long ms)
{
	return (ms * 1000000);
}

long	nano_to_ms(long nano)
{
	return (nano / 1000000);
}
