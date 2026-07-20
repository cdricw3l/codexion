/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:12:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/07/21 00:11:59 by cebouhad         ###   ########.fr       */
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

    t_coder *coders;

    coders = malloc(sizeof(t_coder) * 2);
    assert(coders);

    coders[0].id = 1;
    
    return (0);
}