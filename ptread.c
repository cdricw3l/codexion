/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/20 20:38:15 by cebouhad         ###   ########.fr       */
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

    t_s coder[2];
    pthread_t thread[2];
    int i;
    int arr[2];

    memset(arr, 0 , sizeof(int) * 2);
    printf("conteur 0: %d\n", arr[0]);
    printf("conteur 1: %d\n", arr[1]);
    for (i = 0; i < 2; i++)
    {
        coder[i].id = i;
        coder[i].arr = &arr[0];
        pthread_create(&thread[i], NULL, arr_thread, &coder[i]);
    }
    for (i = 0; i < 2; i++)
    {
        pthread_join(thread[i], NULL);
    }
    printf("conteur 0: %d\n", arr[0]);
    printf("conteur 1: %d\n", arr[1]);
    return (0);
}