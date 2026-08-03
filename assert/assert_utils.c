/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/03 15:47:48 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

int set_params(int *params)
{
    params[number_of_coders] = NB_CODER;
    params[time_to_burnout] = 400;
    params[time_to_compile] = 10;
    params[time_to_debug] = 10;
    params[time_to_refactor] = 10;
    params[number_of_compiles_required] = NB_CR;
    params[dongle_cooldown] = 10;
    params[scheduler] = FIFO ;
    return (TRUE);
}

t_request *_request(int id_request, int id_coder)
{
    t_request *request;

    request = malloc(sizeof(t_request));
    assert(request);
    request->request_id = id_request;
    request->coder_id = (int)id_coder;
    request->last_compilation = 0;
    request->left = NULL;
    request->right = NULL;
    return (request);
}

int remove_request(t_queue *queue)
{
    t_request *request;

    request = queue->request_queue[0];
    if(!pop_request(queue))
    {
        printf("Error remove request %d\n", request->request_id);
        return (FALSE);
    }
    //printf("thread %d remove the request %d new len %zu\n", pthread_self(), request->request_id ,queue->size);
    free(request);
    return (TRUE);
}

int send_request(t_queue *queue)
{
    t_request *request;

    request = _request(queue->request_counter, 0);
    if(!push_request(queue, request))
    {
        printf("Error creation request %d\n", request->request_id);
        return (FALSE);
    }
    //printf("thread %ld pushed the request %d new len %zu\n", pthread_self(), queue->request_counter ,queue->size);
    queue->request_counter++;
    return (TRUE);
}

void get_str_arr_len_assert(void)
{
    char *arr0[] = {"hello", "berlin", "how are you", NULL};
    char *arr1[] = {"hello", "berlin", NULL};
    char *arr2[] = { NULL};
    assert(get_str_arr_len(arr0) == 3);
    assert(get_str_arr_len(arr1) == 2);
    assert(get_str_arr_len(arr2) == 0);
    assert(get_str_arr_len(NULL) == 0);

}
