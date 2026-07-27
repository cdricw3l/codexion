/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/27 15:30:18 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"
#include <malloc.h>

#define FIFO 0
#define BIGGEST 1

#define NB 5
pthread_cond_t cond[5];
pthread_mutex_t mut[5];
pthread_mutex_t q;

typedef struct s_co t_co;
typedef struct s_q t_q;

typedef struct s_co
{

    int             id;
    pthread_cond_t  *c;
    pthread_mutex_t *m;
    t_q         *queue;

} t_co;

typedef struct s_q
{
    int size;
    pthread_mutex_t q;
    t_co *queue[NB];

} t_q;



int save_ticket(t_co *data)
{
    pthread_mutex_lock(&data->queue->q);
    
    if( data->queue->size < NB)
    {
        printf("coder  %d  save is request\n", data->id);
        data->queue->queue[data->queue->size] = data;
        (data->queue->size)++;
        printf("Queue size is %d\n", data->queue->size);

    }
    pthread_mutex_unlock(&data->queue->q);

}

int consume(t_co *data, int methode)
{
    pthread_mutex_lock(&data->queue->q);
    pthread_mutex_lock(data->m);

    int biggest;

    biggest = 0;
    for (int i = 0; i < data->queue->size; i++)
    {
        if (data->queue->queue[i]->id > biggest)
            biggest = data->queue->queue[i]->id;
    }
    printf("coder %d ask for consume\n", data->id);
    printf("id %d\n",data->queue->queue[0]->id);
    if (data->id == biggest)
    {
        printf("coder %d can consume\n", data->id);
        pthread_cond_signal(data->c);
        pthread_mutex_unlock(data->m);
        pthread_mutex_unlock(&data->queue->q);
        return (TRUE);
    }
    pthread_mutex_unlock(data->m);
    pthread_mutex_unlock(&data->queue->q);
    return (FALSE);
}


void *routine(void *arg)
{
    t_co *data = (t_co *)arg;
   
   while (1)
   {
        save_ticket(data);
        sleep(3);
        pthread_mutex_lock(data->m);
        pthread_cond_wait(data->c, data->m);

        while (!consume(data, BIGGEST))
        {
            sleep(1);
        }
        printf("I'm the coder %d\n", data->id);
        pthread_mutex_unlock(data->m);
        sleep(1);
   }
   return (NULL);
    
}

int main(void)
{
    int i;
    t_co co[NB];
    pthread_t thread[NB];
    t_q queue;

    queue.q = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    
    queue.size = 0;
    memset(queue.queue, 0, sizeof(t_co) * NB);
    for (i = 0; i < NB; i++)
    {
        cond[i] = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
        mut[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        co[i].id = i;
        co[i].c = &cond[i]; 
        co[i].m = &mut[i];
        co[i].queue = &queue;
        if(pthread_create(&thread[i], NULL, routine, &co[i]))
        {
            printf("Thread creation error\n");
            exit(1);
        }
        usleep(100000);
    }

    for (i = 0; i < NB; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return (0);
}



