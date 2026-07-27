/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:58 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/27 10:09:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"


int assert_queue()
{
    START_TEST(__func__);
    queue_assert();
    END_TEST(__func__);
    return (0);
}



int main(void)
{
    //asset_utils();
    //assert_thread();
    assert_queue();
    return (0);
}