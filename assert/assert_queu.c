#include "../include/codexion.h"

int queue_assert(void)
{

    t_queue queue;

    queue = init_queue();

    printf("queue addresse %p\n", queue.queue);
    printf("queue size %zu\n", queue.queue_size);
    return (TRUE);
}