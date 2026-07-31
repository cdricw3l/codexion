/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:58 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 08:35:51 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"


int assert_queue()
{
    START_TEST(__func__);
    //poppush_queue_assert();
    bfs_binary_tree_as_arr_assert();
    //create_request_assert();
    //remove_request_assert();
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