/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 08:54:21 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/03 09:13:21 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

int time_assertion(void)
{

    timespec_t  last_compile;
    timespec_t  now;

    clock_t last_n;
    clock_t now_n;

    clock_gettime(CLOCK_MONOTONIC, &last_compile);
    usleep(2000000);
    clock_gettime(CLOCK_MONOTONIC, &now);

    last_n = second_to_nano(last_compile.tv_sec) + last_compile.tv_nsec;
    now_n = second_to_nano(now.tv_sec) + now.tv_nsec;
    printf("last compile %ld\n",  last_n);
    printf("now nano %ld\n", now_n);

    printf("difference between %ld\n", now_n - last_n);

    printf("time elapsed %ld\n", (now_n - last_n) / 1000000);

    return (TRUE);

}