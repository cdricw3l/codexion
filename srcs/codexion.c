/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:16 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/15 18:20:06 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


#define DISPLAY_PARAMS TRUE

int main(int argc, char **argv)
{
    (void) argc;

    t_params params;

    if(parse_arguments(&argv[1], &params) == FALSE)
        return (1);
    if (DISPLAY_PARAMS)
        display_params(params);
    printf("START THREAD\n");
    thead_luncher(&params);
    return (0);
}