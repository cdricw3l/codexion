/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 22:44:36 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"

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

int send_request(t_queue *queue)
{
    t_request *request;

    request = _request(queue->request_counter, pthread_self());
    if(!push_request(queue, request))
    {
        printf("Error creation request %d\n", request->request_id);
        return (FALSE);
    }
    printf("thread %ld pushed the request %zu new len %zu\n", pthread_self(), queue->request_counter ,queue->size);
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