/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:51:52 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/01 15:59:36 by cebouhad         ###   ########.fr       */
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
    request->last_compilation = *coder->last_compilation;
    request->coder_cond_l = &coder->cond_left;
    request->coder_cond_r = &coder->cond_right;
    request->dongle_left = coder->coder_mutex.dongle_l.dongle;
    request->dongle_right = coder->coder_mutex.dongle_r.dongle;
    request->left = NULL;
    request->right = NULL;
    return (request);
}
