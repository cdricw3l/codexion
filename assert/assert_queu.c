#include "../include/codexion.h"

t_request create_request(int id, clock_t last_compile)
{
    t_request request;

    request.id = id;
    request.last_compilation = last_compile;
    request.left = NULL;
    request.right = NULL;
    return (request);
}


int  add_request(t_request **queue, t_request *request)
{
    t_request *root;

    root = *queue;
    if (!root)
        *queue = request;
}

int queue_assert(void)
{

    t_request       **queue;
    t_request r1;


    queue = queue_initialisation();

    r1 = create_request(0, 10);


    free(queue);
    return (TRUE);
}