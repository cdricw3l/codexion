/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:58 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 17:33:23 by cebouhad         ###   ########.fr       */
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
    END_TEST(__func__);
    return (0);
}



int main(void)
{
    //asset_utils();
    assert_thread();
    return (0);
}