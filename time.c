/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/17 12:37:10 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/codexion.h"

int main(void)
{
    struct timespec time;

    clock_gettime(CLOCK_REALTIME, &time);
    printf("%d\n", CLOCK_REALTIME);
    printf("nsec %ld\n", time.tv_nsec);
    printf("sec %ld\n", time.tv_sec);
    time_t t1 = time.tv_nsec;
    usleep(100000);
    clock_gettime(CLOCK_REALTIME, &time);
    time_t t2 = time.tv_nsec;

    printf("%ld\n", t2 - t1);
    return (0);
}