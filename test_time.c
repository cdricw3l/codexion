/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 20:27:09 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/04 20:47:06 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void display_time(timespec_t time)
{
    printf("\nsec: %ld\n", time.tv_sec);
    printf("nano sec: %ld\n", time.tv_nsec);
}

int main(void)
{

    timespec_t start;
    timespec_t end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    usleep(200000);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    display_time(start);
    display_time(end);
    clock_t nano_now = start.tv_nsec + second_to_nano(start.tv_sec);
    clock_t nano_end = end.tv_nsec + second_to_nano(end.tv_sec);
    clock_t diff = nano_end - nano_now;

    printf("elapsed time in ms %ld\n", diff);
    printf("elapsed time in ms %ld\n", nano_to_ms(diff));

    return (0);
}