/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:49:12 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 11:58:28 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	swap_request(t_request **r1, t_request **r2)
{
	t_request	*tmp;

	tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}

void	plug_heap_nodes(t_request **arr, size_t queue_size)
{
	size_t	i;
	size_t	idx_left;
	size_t	idx_right;

	i = 0;
	while (i < queue_size)
	{
		idx_left = (2 * i) + 1;
		idx_right = (2 * i) + 2;
		if (idx_left < queue_size)
			arr[i]->left = arr[idx_left];
		else
			arr[i]->left = NULL;
		if (idx_right < queue_size)
			arr[i]->right = arr[idx_right];
		else
			arr[i]->right = NULL;
		i++;
	}
}
