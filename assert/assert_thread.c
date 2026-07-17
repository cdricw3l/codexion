/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:30:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 17:40:07 by cebouhad         ###   ########.fr       */
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
            assert(get_dongle(i, nb_coder, LEFT) == nb_coder - 1 && get_dongle(i, nb_coder, RIGHT) == 1);
        if(i == nb_coder - 1)
            assert(get_dongle(i, nb_coder, LEFT) == nb_coder - 2 && get_dongle(i, nb_coder, RIGHT) == 0);
        else
            assert(get_dongle(i, nb_coder, LEFT) == i - 1 && get_dongle(i, nb_coder, RIGHT) == i + 1);

    }
    assert(get_dongle(0, nb_coder, RIGHT) == 1);
    return (TRUE);
}