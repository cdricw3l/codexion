#include "../include/codexion.h"





t_queue init_queue(void)
{

    t_queue queue;

    memset(queue.queue, 0, sizeof(queue.queue));
    queue.queue_size = 0;
    return(queue);
}  