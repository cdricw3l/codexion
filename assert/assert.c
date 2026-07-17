/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:58 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 10:07:11 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

int asset_utils()
{
    START_TEST(__func__);
    get_str_arr_len_assert();
    END_TEST(__func__);
    return (0);
}


void print_coder_data(t_coder coder)
{
    printf("id: %d\n", coder.id);
    printf("mutext_1: %p\n", &coder.dongle_l);
    printf("mutext_2: %p\n", &coder.dongle_r);
}


void ft_memcpy(t_coder *c1, t_coder *c2)
{

    unsigned long i;

    i = 0;
    while (i < sizeof(*c1))
    {
        ((unsigned char *)c2)[i] = ((unsigned char * )c1)[i];
        i++;
    }
    
    printf("voici la sie %zu\n", sizeof(*c1));
    printf("voici la sie %zu\n", sizeof(*c2));
}

int test()
{
    t_coder coder;
    t_coder coder2;
    pthread_mutex_t t1;
    pthread_mutex_t t2;


    pthread_mutex_init(&t1, NULL);
    pthread_mutex_init(&t2, NULL);

    coder.id = 0;
    coder.dongle_l = t1;
    coder.dongle_r = t2;
    ft_memcpy(&coder, &coder2);
    print_coder_data(coder);
    print_coder_data(coder2);
    return (0);
}

int main(void)
{
    //asset_utils();
    test();
    return (0);
}