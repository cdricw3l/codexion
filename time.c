/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/20 08:43:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/codexion.h"


void test_time()
{
    struct timespec time1;
    struct timespec time2;
    int i = 100;
    int j;
    memset(&time1, 0, sizeof(struct timespec));
    memset(&time2, 0, sizeof(struct timespec));
    while (i >= 0)
    {
        j = clock_gettime(CLOCK_MONOTONIC_RAW, &time1);
        time_t t1 = time1.tv_nsec;

        printf("j: %d nsec %ld\n", j, time1.tv_nsec);
        usleep(200000);
        j = clock_gettime(CLOCK_MONOTONIC_RAW, &time2);
        u_int64_t t2 = time2.tv_nsec;
        printf("j: %d nsec %ld\n", j, time2.tv_nsec);
        printf("%ld\n", (t2 - t1));
        i--;
    }
    
    
}


time_t time_diff(time_t start, time_t end)
{
    time_t elapsed;

    if ((end - start) < 0)
        elapsed =  1000000000 + end - start;
    else
        elapsed = end - start;
    
    return elapsed;
}



void *thread(void *data)
{
    int i;
    pthread_t id;
    struct timespec start;
    struct timespec end;
    
    i = 10;
    memset(&start, 0, sizeof(struct timespec));
    memset(&end, 0, sizeof(struct timespec));
    id = pthread_self();
    while (i >= 0)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        usleep(200000);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("[thread %ld]elapsed time %ld\n", id,  time_diff(start.tv_nsec, end.tv_nsec));
        i--;
    }
    return (NULL);
}

int main(void)
{
    pthread_t t1;
    pthread_t t2;
    

    pthread_create(&t1, NULL, thread, NULL);
    pthread_create(&t2, NULL, thread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return (0);
}