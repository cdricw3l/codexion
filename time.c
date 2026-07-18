/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/18 22:43:13 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/codexion.h"


void test_time()
{
    struct timespec time;
    int i = 100;


    while (i >= 0)
    {
        clock_gettime(1, &time);
        time_t t1 = time.tv_nsec;

        printf("nsec %ld\n", time.tv_nsec);
        usleep(200000);
        clock_gettime(1, &time);
        time_t t2 = time.tv_nsec;
        printf("nsec %ld\n", time.tv_nsec);
        printf("%ld\n", (t2 - t1) );
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