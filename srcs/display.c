/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 08:36:06 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void display_params(t_params param)
{
    printf(BHGRN"Program settings:\n");
    printf(HBLU"[Number of philosopher]:"HYEL" %zu\n", param.coder);
    printf(HBLU"[Time to burnout]:"HYEL" %zu\n", param.ttb);
    printf(HBLU"[Time to compile]:"HYEL" %zu\n", param.ttc);
    printf(HBLU"[Time to debug]:"HYEL" %zu\n", param.ttd);
    printf(HBLU"[Time to refactor]:"HYEL" %zu\n", param.ttr);
    printf(HBLU"[Number of compiles required]:"HYEL" %zu\n", param.ncr);
    printf(HBLU"[Dongle cooldown]:"HYEL" %zu\n", param.dc);
    printf(HBLU"[scheduler]: "HYEL);
    if (param.scheduler == FIFO)
        printf("edf"CRESET"\n");
    else if (param.scheduler == EDF)
        printf("edf"CRESET"\n");
}