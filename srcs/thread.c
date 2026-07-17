/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:53:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 08:45:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void *coder_thread(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    printf(HCYN"i'm the coder number %d\n"CRESET, coder->id);
    return (NULL);
}

// int get_dongle(int id, int number_of_coder)
// {
//     if (id == 0)
//     {

//     }
// }

int thead_luncher(t_params *param, mutex dongles[CODER_MAX])
{
    printf("START coder %d\n", 0);

    size_t i;
    //pthread_t           thread[CODER_MAX];
    t_coder             coder[CODER_MAX];

    i = 0;
    (void) dongles;

    while (i < param->coder)
    {

        coder[i].id = i;
        coder[i].param = param;
        //pthread_create(&thread[i], NULL, coder_thread, &coder[i]);
        usleep(200);
        i++;
    }
    i = 0;
    // while(i < param->coder)
    // {
    //     pthread_join(thread[i++], NULL);
    //     printf("Fin du thread %zu\n", i);
    // }
    return (TRUE);
}
