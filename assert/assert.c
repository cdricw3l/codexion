/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:58 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 21:06:20 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"


int assert_queue()
{
    // poppush_queue_assert();
    // bfs_binary_tree_as_arr_assert();
    // push_request_assert();
    //create_request_assert();
    //remove_request_assert();
    return (0);
}

int asset_thread(void)
{
    thread_request_assert();
    return (0);
}

int main(void)
{
    //asset_utils();
    //assert_thread();
    //assert_queue();
    asset_thread();
    return (0);
}