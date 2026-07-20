/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 12:20:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/20 19:26:51 by cebouhad         ###   ########.fr       */
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

struct timespec time_diff(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec + - start.tv_sec - 1;
        temp.tv_nsec =  1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

clock_t time_calculation(struct timespec time)
{
    /* convert second to nano*/
    clock_t n_to_sec;

    n_to_sec  = time.tv_sec * 1000000000;
    return ((n_to_sec + time.tv_nsec) / 1000000);
}

struct s_mu
{
    pthread_mutex_t *mu_memset;
    pthread_mutex_t *mu_printf;
    struct timespec start;
    int id;
};


void *thread(void *data)
{
    pthread_t id;
    struct s_mu *mu; 
    struct timespec end;
    clock_t timestamp;

    id = pthread_self();
    
    mu = (struct s_mu *)data;
    printf("Start thread %p\n", &(mu->mu_memset));
    
    pthread_mutex_lock(mu->mu_memset);
    printf("resultat du lock\n");
    memset(&end, 0, sizeof(struct timespec));
    pthread_mutex_unlock(mu->mu_memset);
    while (1)
    {
        clock_gettime(CLOCK_MONOTONIC, &end);
        timestamp = time_calculation(time_diff(mu->start, end));
        printf("%ld %d start sleep\n", timestamp, mu->id);
        usleep(200000);
        clock_gettime(CLOCK_MONOTONIC, &end);
        timestamp = time_calculation(time_diff(mu->start, end));
        printf("%ld %d end sleep\n", timestamp , mu->id);
        pthread_mutex_lock(mu->mu_printf);
        pthread_mutex_unlock(mu->mu_printf);
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
    struct timespec tm;

    mu = malloc(sizeof(struct s_mu));
    assert(mu);
    assert(pthread_mutex_init(&m1, NULL) == 0);
    assert(pthread_mutex_init(&m2, NULL) == 0);
    mu->mu_memset = &m1;
    mu->mu_printf = &m2;
    clock_gettime(CLOCK_MONOTONIC, &tm);
    mu->start = tm;
    mu->id = 1;
    pthread_create(&t1, NULL, thread, mu);
    //pthread_create(&t2, NULL, thread, &mu);
    pthread_join(t1, NULL);
    //pthread_join(t2, NULL);
    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);

    return (0);
}