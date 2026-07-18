/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/18 00:41:20 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/codexion.h"


void test_time()
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
    void *arr[4];

    arr[0] = compile;
    arr[1] = refacto;
    arr[2] = release;
    arr[3] = NULL;

    int i = 0;
    while (arr[i])
    {
        void (*f)() = arr[i];
        f();
        i++;
    }
    

    return (0);
}