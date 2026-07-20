/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/20 21:39:55 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


typedef struct s_s
{
    int id;
    int *arr;

} t_s;


void *arr_thread(void *data)
{
    t_s *coder;

    coder = (t_s *)data;

    for (int i = 0; i < 100; i++)
    {
        (*coder->arr)++;
    }
    return (NULL);
}


int main(void)
{

    pthread_mutex_t mu;

    printf("init test %d\n",    pthread_mutex_init(&mu, NULL));
    printf("destroy test %d\n", pthread_mutex_destroy(&mu));
    return (0);
}