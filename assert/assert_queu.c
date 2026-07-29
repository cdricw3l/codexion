#include "../include/codexion.h"


t_request create_request(int coder_id, int request_id ,clock_t last_compile, pthread_cond_t *cond)
{
    t_request request;

    request.coder_id = coder_id;
    request.request_id = request_id;
    request.last_compilation = last_compile;
    request.cond = cond;
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
    pthread_cond_t cond[11];


    for (int i = 0; i < 11; i++)
        cond[i] = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    queue_initialisation(11, &queue);

    r1 = create_request(24,0, 10, &cond[0]);
    r2 = create_request(24,1, 100, &cond[1]);
    r3 = create_request(24,2, 100, &cond[2]);
    r4 = create_request(24,3, 100, &cond[3]);
    r5 = create_request(24,4, 100, &cond[4]);
    r6 = create_request(24,5, 100, &cond[5]);
    r7 = create_request(24,6, 100, &cond[6]);
    r8 = create_request(24,7, 100, &cond[7]);
    r9 = create_request(24,8, 100, &cond[8]);
    r10 = create_request(24,9, 100, &cond[9]);
    r11 = create_request(24,10, 100, &cond[9]);


    r1.left = &r2;
    r1.right = &r3;

    r2.left = &r4;
    r2.right = &r5;

    r3.left = &r6;
    r3.right = &r7;

    r4.left = &r8;
    r4.right = &r9;

    r5.left = &r10;
    r5.right = &r11;

    queue.size = 11;
    *queue.request_queue = &r1;
    
    t_request new;
    t_request new2;
    new = create_request(24,-1, 10, &cond[0]);
    new2 = create_request(24, 11, 10, &cond[0]);

    printf("new request\n");
    insert_request(&queue, &new);
    printf("new request\n");
    insert_request(&queue, &new2);

    free(queue.request_queue);
    return (TRUE);
}