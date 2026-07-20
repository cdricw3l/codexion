/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/20 11:23:22 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


typedef struct s_s
{
    int id;
    pthread_mutex_t *mu;

} t_s;


void d_coder(t_s *coder)
{
    int j;

    printf("coder id: %d\n", coder->id);
    for(j = 0; j < 2; j++)
        printf("mutex: %p\n", &coder->mu[j]);
}

int main(void)
{

    pthread_mutex_t mu[2];
    t_s coder[2];
    int i;

    for (i = 0; i < 2; i++)
        pthread_mutex_init(&mu[i], NULL);
    for (i = 0; i < 2; i++)
    {
        coder[i].id = i;
        coder[i].mu = (pthread_mutex_t *)&mu;
        d_coder(&coder[i]);
    }
    
    return (0);
}