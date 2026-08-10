/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:30:54 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 11:45:10 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


typedef struct s_d1
{
    long __sig;
	char __opaque[__PTHREAD_MUTEX_SIZE__];


} t_d1;

typedef struct s_d2
{
    clock_t         last_use;
    int             dongle_id;
    int             queue_size;
   
} t_d2;

int main(void)
{

    t_d1 d1;
    t_d2 d2;

    printf("size: %zu\n", sizeof(long));
    printf("size: %zu\n", sizeof(d2));
    return (0);
}