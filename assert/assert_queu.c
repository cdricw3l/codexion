/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_queu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:12:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/30 19:00:38 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

t_request create_request(int coder_id, int request_id ,clock_t last_compile)
{
    t_request request;

    request.coder_id = coder_id;
    request.request_id = request_id;
    request.last_compilation = last_compile;
    request.left = NULL;
    request.right = NULL;
    return (request);
}


static int get_size_queue(t_request **queue)
{
    int i;

    i = 0;
    while (queue[i])
        i++;
    return (i);    
}

void poppush_queue_assert(void)
{
    START_TEST(__func__);
    t_request	**queue;
    int         nb_request;
    int         size_q;
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;

    nb_request = 4;
    size_q = 0;
    queue = malloc(sizeof(t_request *) * nb_request);
    assert(queue);
    memset(queue, 0, sizeof(t_request *) * nb_request);

    for (int i = 0; i < nb_request; i++)
    {
        queue[i] = NULL;
        printf("queue %p\n", queue[i]);
    }
    
    // assert(get_size_queue(queue) == 0);
    // r1 = create_request(24,0, 10);
    // r2 = create_request(24,1, 100);
    // r3 = create_request(24,2, 100);
    // r4 = create_request(24,4, 100);
    
    // push(queue, &r1);
    // printf("La taille de la queue est %d\n", get_size_queue(queue));
    // assert(get_size_queue(queue) == 1);
    // push(queue, &r2);
    // assert(get_size_queue(queue) == 2);
    // push(queue, &r3);
    // assert(get_size_queue(queue) == 3);
    // push(queue, &r4);
    // printf("La taille de la queue est %d\n", get_size_queue(queue));
    // assert(get_size_queue(queue) == 4);
    

    //pop(queue, get_size_queue(queue));
    // for (int i = 0; queue[i]; i++)
    //     printf("request %d\n", queue[i]->request_id);
    // assert(get_size_queue(queue) == 3);


    END_TEST(__func__);

}


int create_request_assert(void)
{
    START_TEST(__func__);
    t_queue   queue;
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request r5;
    t_request r6;
    t_request r7;
    t_request r8;
    t_request r9;
    t_request r10;
    t_request r11;
    t_request r12;
    t_request r13;


    queue_initialisation(&queue);
    r1 = create_request(24,0, 10);
    r2 = create_request(24,1, 100);
    r3 = create_request(24,2, 100);
    r4 = create_request(24,3, 100);
    r5 = create_request(24,4, 100);
    r6 = create_request(24,5, 100);
    r7 = create_request(24,6, 100);
    r8 = create_request(24,7, 100);
    r9 = create_request(24,8, 100);
    r10 = create_request(24,9, 100);
    r11 = create_request(24,10, 100);
    r12 = create_request(24,-10, 100);
    r13 = create_request(24, -5, 100);

    queue.size = 0;
    insert_request(&queue, &r1);
    assert(queue.size == 1);
    assert(queue.request_queue[0]->request_id == 0);
    insert_request(&queue, &r2);
    assert(queue.size == 2);
    assert(queue.request_queue[0]->request_id == 0);

    t_request **arr = bfs_binary_tree_as_arr(&queue);
    assert(arr);
    // insert_request(&queue, &r3);
    // assert(queue.size == 3);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r4);
    // assert(queue.size == 4);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r5);
    // assert(queue.size == 5);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r6);
    // assert(queue.size == 6);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r7);
    // assert(queue.size == 7);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r8);
    // assert(queue.size == 8);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r9);
    // assert(queue.size == 9);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r10);
    // assert(queue.size == 10);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r11);
    // assert(queue.size == 11);
    // assert(queue.request_queue[0]->request_id == 0);
    // insert_request(&queue, &r12);
    // assert(queue.size == 12);
    // assert((*(queue.request_queue))->request_id == -10);
    
    // insert_request(&queue, &r13);
    // assert(queue.size == 13);
    // printf("STATE BEFORT POP");
    // display_tree(*(queue.request_queue));
    // assert((*(queue.request_queue))->request_id == -10);
    // assert((*(queue.request_queue))->left->request_id == -5);
    free(queue.request_queue);
    END_TEST(__func__);
    return (TRUE);
}


int remove_request_assert(void)
{
    START_TEST(__func__);
    t_queue   queue;
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request r5;

    r1 = create_request(24,0, 10);
    r2 = create_request(24,1, 100);
    r3 = create_request(24,2, 100);
    r4 = create_request(24,3, 100);
    r5 = create_request(24,-10, 100);

    queue_initialisation(&queue);
    insert_request(&queue, &r1);
    insert_request(&queue, &r2);
    insert_request(&queue, &r3);
    insert_request(&queue, &r4);
    insert_request(&queue, &r5);

    display_tree(*queue.request_queue);
    pop_request(&queue);
    display_tree(*queue.request_queue);
    END_TEST(__func__);
    return (TRUE);
}