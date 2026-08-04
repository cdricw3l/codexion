/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_queu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:12:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 01:50:10 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

t_request assert_create_request(int coder_id, int request_id , clock_t last_compile)
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

/* 
    Assertion for push and pop methode.
    push and pop are used for the bfs array construction;
*/
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
    queue = malloc(sizeof(t_request *) * (nb_request + 1));
    assert(queue);
    memset(queue, 0, sizeof(t_request *) * (nb_request + 1));
    r1 = assert_create_request(24,0, 10);
    r2 = assert_create_request(24,1, 100);
    r3 = assert_create_request(24,2, 100);
    r4 = assert_create_request(24,4, 100);
    push(queue, &r1);
    push(queue, &r2);
    assert(get_size_queue(queue) == 2);
    push(queue, &r3);
    assert(get_size_queue(queue) == 3);
    push(queue, &r4);
    assert(get_size_queue(queue) == 4);
    // printf("after all push\n");
    // for (i = 0; i < nb_request; i++)
    // {
    //     printf("queue %p\n", queue[i]);
    // }
    pop(queue, get_size_queue(queue));
    assert(get_size_queue(queue) == 3);
    //printf("after one pop\n");
    // for (i = 0; i < nb_request; i++)
    // {
    //     printf("queue %p\n", queue[i]);
    // }
    pop(queue, get_size_queue(queue));
    assert(get_size_queue(queue) == 2);
    pop(queue, get_size_queue(queue));
    assert(get_size_queue(queue) == 1);
    pop(queue, get_size_queue(queue));
    assert(get_size_queue(queue) == 0);
  
    push(queue, &r4);
    assert(get_size_queue(queue) == 1);
    free(queue);
    END_TEST(__func__);

}


int bfs_binary_tree_as_arr_assert(void)
{
    START_TEST(__func__);

    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request r5;
    t_request r6;
    t_request r7;
    

    r1 = assert_create_request(24,0, 10);
    r2 = assert_create_request(24,1, 100);
    r3 = assert_create_request(24,2, 100);
    r4 = assert_create_request(24,3, 100);
    r5 = assert_create_request(24,4, 100);
    r6 = assert_create_request(24,5, 100);
    r7 = assert_create_request(24,6, 100);
    

    r1.left = &r2;
    r1.right = &r3;

    r2.left = &r4;
    r2.right = &r5;

    r3.left = &r6;
    r3.right = &r7;

    t_request **arr;
    t_queue *queue;

    queue = queue_initialisation(FIFO, 0);
    assert(queue);
    *queue->request_queue = &r1;

    queue->size = count_tree_node(*queue->request_queue, 0) - 1;
    assert(queue->size == 7);
    arr = bfs_binary_tree_as_arr(queue);

    assert(arr[0] == &r1);
    assert(arr[1] == &r2);
    assert(arr[2] == &r3);
    assert(arr[3] == &r4);
    assert(arr[4] == &r5);
    assert(arr[5] == &r6);
    assert(arr[6] == &r7);
    assert(arr[7] == NULL);
    assert(bfs_binary_tree_as_arr(NULL) == NULL);
    free(arr);
    free(queue->request_queue);
    free(queue);
    END_TEST(__func__);
    return (TRUE);
}

int push_request_assert(void)
{
    START_TEST(__func__);

    t_request **arr;
    
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request r5;

    r1 = assert_create_request(24,-1, 10);
    r2 = assert_create_request(24,0, 100);
    r3 = assert_create_request(24,2, 100);
    r4 = assert_create_request(24,-20, 100);
    r5 = assert_create_request(24,200, 100);

    arr = malloc(sizeof(t_request *) * 6);
    memset(arr, 0, sizeof(t_request * ) * 6);
    assert(arr);
    arr[0] = &r1;
    assert(arr[0]->request_id == -1);
    
    arr[1] = &r2;
    add_request(arr, 2, FIFO);
    assert(arr[0]->request_id == -1);
    assert(arr[1]->request_id == 0);
    arr[2] = &r3;
    add_request(arr, 3, FIFO);
    assert(arr[0]->request_id == -1);
    assert(arr[1]->request_id == 0);
    assert(arr[2]->request_id == 2);
    arr[3] = &r4;
    
    add_request(arr, 4, FIFO);
   
    assert(arr[0]->request_id == -20);
    assert(arr[1]->request_id == -1);
    assert(arr[2]->request_id == 2);
    assert(arr[3]->request_id == 0);
    for (int i = 0; i < 4;i++)
        assert(!arr[i]->left  && !arr[i]->right);

    plug_heap_nodes(arr, 4);
    assert(arr[0]->left == arr[1]);
    assert(arr[0]->right == arr[2]);
    assert(arr[1]->left == arr[3]);
    assert(arr[1]->right == NULL);
    assert(arr[2]->left == NULL);
    assert(arr[2]->right == NULL);
    assert(arr[3]->left == NULL);
    assert(arr[3]->right == NULL);

    arr[4] = &r5;
    add_request(arr, 5, FIFO);
    plug_heap_nodes(arr, 5);
    assert(arr[0]->left == arr[1]);
    assert(arr[0]->right == arr[2]);
    assert(arr[1]->left == arr[3]);
    assert(arr[1]->right == arr[4]);
    assert(arr[2]->left == NULL);
    assert(arr[2]->right == NULL);
    assert(arr[3]->left == NULL);
    assert(arr[3]->right == NULL);
    assert(arr[4]->left == NULL);
    assert(arr[4]->right == NULL);

    free(arr);
    END_TEST(__func__);
    return (TRUE);
    
}

int create_request_assert(void)
{
    START_TEST(__func__);
    t_queue   *queue;
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request r5;
    t_request r6;
    t_request r7;
    t_request r8;


    queue =  queue_initialisation(FIFO, 0);
    assert(queue);
    r1 = assert_create_request(24,0, 10);
    r2 = assert_create_request(24,1, 100);
    r3 = assert_create_request(24,2, 100);
    r4 = assert_create_request(24,3, 100);
    r5 = assert_create_request(24,4, 100);
    r6 = assert_create_request(24,5, 100);
    r7 = assert_create_request(24,6, 100);
    r8 = assert_create_request(24,7, 100);
   

    queue->size = 0;
    push_request(queue, &r1);
    assert(queue->size == 1);
    assert(queue->request_queue[0]->request_id == 0);
    push_request(queue, &r2);
    assert(queue->size == 2);
    assert(queue->request_queue[0]->request_id == 0);
    push_request(queue, &r3);
    assert(queue->size == 3);
    assert(queue->request_queue[0]->request_id == 0);
    push_request(queue, &r4);
    assert(queue->size == 4);
    assert(queue->request_queue[0]->request_id == 0);
    push_request(queue, &r5);
    assert(queue->size == 5);
    assert(queue->request_queue[0]->request_id == 0);
    push_request(queue, &r6);
    assert(queue->size == 6);
    assert(queue->request_queue[0]->request_id == 0);
    push_request(queue, &r7);
    assert(queue->size == 7);
    assert(queue->request_queue[0]->request_id == 0);
    push_request(queue, &r8);
    assert(queue->size == 8);
    assert(queue->request_queue[0]->request_id == 0);
    free(queue->request_queue);
    free(queue);
    END_TEST(__func__);
    return (TRUE);
}


int remove_request_assert(void)
{
    START_TEST(__func__);
    t_queue   *queue;
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request r5;
    t_request r6;

    r1 = assert_create_request(24,0, 10);
    r2 = assert_create_request(24,1, 100);
    r3 = assert_create_request(24,2, 100);
    r4 = assert_create_request(24,3, 100);
    r5 = assert_create_request(24,-10, 100);
    r6 = assert_create_request(24,-7, 100);

    queue = queue_initialisation(FIFO, 0);
    push_request(queue, &r1);
    push_request(queue, &r2);
    push_request(queue, &r3);
    push_request(queue, &r4);
    push_request(queue, &r5);
    push_request(queue, &r6);

    pop_request(queue);
    assert(queue->size == 5);
    assert(queue->request_queue[0]->request_id == -7);
    pop_request(queue);
    assert(queue->size == 4);
    assert(queue->request_queue[0]->request_id == 0);
    pop_request(queue);
    assert(queue->size == 3);
    assert(queue->request_queue[0]->request_id == 1);
    pop_request(queue);
    assert(queue->size == 2);
    assert(queue->request_queue[0]->request_id == 2);
    pop_request(queue);
    assert(queue->size == 1);
    assert(queue->request_queue[0]->request_id == 3);
    pop_request(queue);
    assert(queue->size == 0);
    free(queue->request_queue);
    free(queue);
    END_TEST(__func__);
    return (TRUE);
}

int efd_assert(void)
{
    START_TEST(__func__);
    t_queue   *queue;
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request r5;
    t_request r6;
    int i;

    r1 = assert_create_request(24,0, 10);
    r2 = assert_create_request(24,1, 20);
    r3 = assert_create_request(24,2, 30);
    r4 = assert_create_request(24,3, 40);
    r5 = assert_create_request(24,-10, 50);
    r6 = assert_create_request(24,-7, 60);

    queue = queue_initialisation(EDF , 300);
    push_request(queue, &r1);
    assert(queue->request_queue[0]->last_compilation == (clock_t)10);
    push_request(queue, &r2);
    assert(queue->request_queue[0]->last_compilation == (clock_t)20);
    push_request(queue, &r3);
    assert(queue->request_queue[0]->last_compilation == (clock_t)30);
    push_request(queue, &r4);
    assert(queue->request_queue[0]->last_compilation == (clock_t)40);
    push_request(queue, &r5);
    assert(queue->request_queue[0]->last_compilation == (clock_t)50);
    push_request(queue, &r6);
    assert(queue->request_queue[0]->last_compilation == (clock_t)60);

    pop_request(queue);
    assert(queue->request_queue[0]->last_compilation == 50);
    pop_request(queue);
    assert(queue->request_queue[0]->last_compilation == 40);
    pop_request(queue);
    assert(queue->request_queue[0]->last_compilation == 30);
    pop_request(queue);
    assert(queue->request_queue[0]->last_compilation == 20);
    pop_request(queue);
    assert(queue->request_queue[0]->last_compilation == 10);
    pop_request(queue);
    assert(queue->request_queue[0] == NULL);
    
    free(queue->request_queue);
    free(queue);
    END_TEST(__func__);
    return (TRUE);
}