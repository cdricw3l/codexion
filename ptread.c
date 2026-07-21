/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/21 17:16:46 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


typedef struct s_planish
{
    int id;
    int p;
    pthread_cond_t c;
    pthread_mutex_t m;

} t_planish;


void *replanishment(void *data)
{

    t_planish *p;

    p = (t_planish *)data;
    while (1)
    {
        pthread_mutex_lock(&p->m);
        pthread_cond_wait(&p->c, &p->m);
        printf("Start replanishment\n");
        
        p->p = 10;
     
        pthread_cond_signal(&p->c);
        pthread_mutex_unlock(&p->m);
    }
    return (NULL);
}

void *consumer(void *data)
{
    t_planish *p;

    p = (t_planish *)data;
    while (1)
    {

        pthread_mutex_lock(&p->m);
        if (p->p <= 0)
        {
            printf("Start consumer %d\n", p->id);

            pthread_cond_signal(&p->c);
            pthread_cond_wait(&p->c, &p->m);
        }
        printf("le clien [%d] prend 1 bonbon reste %d\n",p->id, p->p);
        p->p--;
        pthread_mutex_unlock(&p->m);
        sleep(1);
    }
    return (NULL);
}


int main(void)
{

    t_planish planish[2];
    pthread_t consume[2];
    pthread_t replanish;

    
    planish[0].c = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    planish[0].m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    planish[0].p = 0;
    planish[0].id = 0;
    planish[1].c = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    planish[1].m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    planish[1].p = 0;
    planish[1].id = 1;

    if(pthread_create(&replanish, NULL, replanishment, &planish[0]))
    {
        perror("planish thread error\n");
        return (1);
    }
    // if(pthread_create(&consume[0], NULL, consumer, &planish[0]))
    // {
    //     perror("consumer thread error\n");
    //     return (1);
    // }
    if(pthread_create(&consume[1], NULL, consumer, &planish[1]))
    {
        perror("consumer thread error\n");
        return (1);
    }
   
    
    pthread_join(consume[0], NULL);
    pthread_join(consume[1], NULL);
    pthread_join(replanish, NULL);
    
    return (0);
}