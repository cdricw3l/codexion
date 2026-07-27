/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/23 13:37:48 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


void mutex_data(pthread_mutex_t *mu)
{
    printf("[ Mutex data ]\n");
    printf("size: %s\n", mu->__size);
    printf("align: %ld\n", mu->__align);
    printf("structure adress %p\n", &mu->__data);
    printf("count: %d\n",mu->__data.__count);
    printf("elision: %d\n",mu->__data.__elision);
    printf("kind: %d\n",mu->__data.__kind);
    printf("lock: %d\n",mu->__data.__lock);
    printf("nuser: %d\n",mu->__data.__nusers);
    printf("owner: %d\n",mu->__data.__owner);
    printf("spin %d\n",mu->__data.__spins);
    printf("list %p\n", &mu->__data.__list);
    printf("\n");

}

typedef struct s_data
{
    int                 id;
    int                 number_of_eating;
    int                 *stock;
    pthread_mutex_t     *mu_stock;
    pthread_cond_t      *cond_stock;

} t_data;



void display_time(struct timespec tm)
{
    printf("sec: %ld\n", tm.tv_sec);
    printf("nsec: %ld\n", tm.tv_nsec);
    printf("\n");
}


void cooldown(int ms, pthread_cond_t *cond, pthread_mutex_t *mu)
{
    int rt = 0;
    struct timespec future;
    struct timespec start;
    struct timespec end;

    clock_gettime(CLOCK_REALTIME, &start);
    future = futuristic_timespec(ms);
    pthread_mutex_lock(mu);
    while (rt == 0)
        rt = pthread_cond_timedwait(cond, mu, &future);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Elapsed time %ld\n", time_calculation(time_diff(start, end)));
    pthread_mutex_unlock(mu);
}



void *consume(void *d)
{
    t_data *data;

    data = (t_data *)d;
    while (1)
    {
        pthread_mutex_lock(data->mu_stock);
        if(*(data->stock) <= 0)
        {
            printf("Thread %d say Stock is empty\n", data->id);
            pthread_cond_signal(data->cond_stock);
            pthread_cond_wait(data->cond_stock, data->mu_stock);

        }
        (*(data->stock))--;
        data->number_of_eating++;
        printf("Thread %d consume one. Number of eating: %d new stock %d/[10]\n", data->id, data->number_of_eating, *(data->stock));
        pthread_mutex_unlock(data->mu_stock);
        sleep(1);
    }
    return (NULL);
}



void *replanish(void *d)
{
    t_data *data;

    data = (t_data *)d;
    while (1)
    {
        pthread_mutex_lock(data->mu_stock);
        /* 
            pthread_cond_wait libere le mutex mu_stock et met en attente le thread  qui ecoute sur data->cond_stock 
            Quand un signal est envoyer a data->cond_stock le thread lock le mutex mu_stock 
        */
        pthread_cond_wait(data->cond_stock, data->mu_stock);
        while ((*data->stock) < 10)
        {
            (*data->stock)++;
            printf("replanishment %d/[10]\n", *data->stock);
            usleep(700000);
        }
        pthread_mutex_unlock(data->mu_stock);
        pthread_cond_broadcast(data->cond_stock);
    }
}

#define NB 10

int main(void)
{
    t_data data[NB];
    pthread_t thread[NB];
    pthread_t replanishment;

    int stock;
    int i;
    pthread_mutex_t mu_stock;
    pthread_cond_t cond_stock;

    pthread_mutex_init(&mu_stock, NULL);
    pthread_cond_init(&cond_stock, NULL);
    stock = 10;

    for (i = 0; i < NB; i++)
    {
        data[i].id = i;
        data[i].number_of_eating = 0;
        data[i].mu_stock = &mu_stock;
        data[i].cond_stock = &cond_stock;
        data[i].stock = &stock; 
    }

    pthread_create(&replanishment, NULL, replanish, &data[0]);
    for (i = 0; i < NB; i++)
    {
        pthread_create(&thread[i], NULL, consume, &data[i]);
        usleep(50000);
    }

    for (i = 0; i < NB; i++)
        pthread_join(thread[i], NULL);
    
    return (0);
}






