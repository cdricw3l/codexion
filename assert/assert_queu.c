#include "../include/codexion.h"


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






int queue_assert(void)
{

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


    queue_initialisation(13, &queue);

    r1 = create_request(24,-10, 10);
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
    assert(queue.request_queue[0]->request_id == -10);
    insert_request(&queue, &r2);
    assert(queue.size == 2);
    assert(queue.request_queue[0]->request_id == -10);
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
   
    insert_request(&queue, &r13);
    assert(queue.size == 3);
    display_tree(*(queue.request_queue));
    // assert((*(queue.request_queue))->request_id == -10);
    // assert((*(queue.request_queue))->left->request_id == -5);
    free(queue.request_queue);
    return (TRUE);
}