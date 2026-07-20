/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/20 10:26:23 by cebouhad         ###   ########.fr       */
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
    
    return elapsed / 1000000;
}

struct s_mu
{
    pthread_mutex_t *mu_memset;
    pthread_mutex_t *mu_printf;
};


void *thread(void *data)
{
    int i;
    pthread_t id;
    struct s_mu *mu; 
    struct timespec start;
    struct timespec end;
    
    id = pthread_self();
    
    i = 10;
    mu = (struct s_mu *)data;
    printf("Start thread %p\n", &(mu->mu_memset));
    
    pthread_mutex_lock(mu->mu_memset);
    printf("resultat du lock\n");
    memset(&start, 0, sizeof(struct timespec));
    memset(&end, 0, sizeof(struct timespec));
    pthread_mutex_unlock(mu->mu_memset);
    printf("resultat du unlock\n");
    while (i >= 0)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        usleep(200000);
        clock_gettime(CLOCK_MONOTONIC, &end);
        pthread_mutex_lock(mu->mu_printf);
        printf("[thread %ld]elapsed time %ld\n", id,  time_diff(start.tv_nsec, end.tv_nsec));
        pthread_mutex_unlock(mu->mu_printf);
        i--;
    }
    return (NULL);
}


int main(void)
{
    pthread_t t1;
    pthread_t t2;
    pthread_mutex_t m1;
    pthread_mutex_t m2;
    struct s_mu *mu;

    mu = malloc(sizeof(struct s_mu));
    assert(mu);
    assert(pthread_mutex_init(&m1, NULL) == 0);
    assert(pthread_mutex_init(&m2, NULL) == 0);
    mu->mu_memset = &m1;
    mu->mu_printf = &m2;
    pthread_create(&t1, NULL, thread, mu);
    //pthread_create(&t2, NULL, thread, &mu);
    pthread_join(t1, NULL);
    //pthread_join(t2, NULL);
    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);

    return (0);
}