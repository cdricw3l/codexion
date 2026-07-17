/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:30:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 22:42:47 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int get_dongle(int id, int number_of_coder, int type);

int get_dongle_assert(void)
{
    int nb_coder;
    int i;
    nb_coder = 10;

    for (i = 0; i < nb_coder; i++)
    {
        if(i == 0)
        {
            assert(get_dongle(i, nb_coder, LEFT) == nb_coder - 1);
            assert(get_dongle(i, nb_coder, RIGHT) == i);

        }
        else
        {
            assert(get_dongle(i, nb_coder, LEFT) == i - 1);
            assert(get_dongle(i, nb_coder, RIGHT) == i);
        }
    }
    return (TRUE);
}