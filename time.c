/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/20 08:15:37 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/codexion.h"


void test_time()
{
    struct timespec time1;
    struct timespec time2;
    int i = 100;

    memset(&time1, 0, sizeof(struct timespec));
    memset(&time2, 0, sizeof(struct timespec));
    while (i >= 0)
    {
        clock_gettime(CLOCK_MONOTONIC, &time1);
        time_t t1 = time1.tv_nsec;

        printf("nsec %ld\n", time1.tv_nsec);
        usleep(200000);
        clock_gettime(CLOCK_MONOTONIC, &time2);
        u_int64_t t2 = time2.tv_nsec;
        printf("nsec %ld\n", time2.tv_nsec);
        printf("%ld\n", (t2 - t1));
        i--;
    }
    
    
}

int compile()
{
    printf("Compile\n");
    sleep(3);
    return (TRUE);
}

int refacto()
{
    printf("Refacto\n");
    sleep(3);
    return (TRUE);
}
int release()
{
    printf("Release\n");
    sleep(3);
    return (TRUE);
}

int main(void)
{
    test_time();
    

    return (0);
}