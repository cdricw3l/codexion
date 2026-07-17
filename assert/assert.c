/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:58 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 22:48:27 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

int asser_utils()
{
    START_TEST(__func__);
    get_str_arr_len_assert();
    END_TEST(__func__);
    return (0);
}

int assert_thread()
{
    START_TEST(__func__);
    get_dongle_assert();
    mutex_initialisation_assert();
    END_TEST(__func__);
    return (0);
}



int main(void)
{
    //asset_utils();
    assert_thread();
    return (0);
}