/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:51:52 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/02 15:07:42 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_request *create_request(t_coder *coder)
{
    t_request *request;

    request = malloc(sizeof(t_request));
    if (!request)
        return (NULL);
    request->coder_id = coder->id;
    request->request_id = coder->queue->request_counter;
    request->last_compilation = coder->last_compilation;
    request->cond = &coder->cond;
    request->mu = coder->coder_mutex.coder_mutex;
    request->left = NULL;
    request->right = NULL;
    return (request);
}
