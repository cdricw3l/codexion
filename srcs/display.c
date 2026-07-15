/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/15 17:56:48 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void display_params(t_params param)
{
    printf(BHGRN"Program settings:\n");
    printf(HBLU"[Number of philosopher]:"HYEL" %d\n", param.nb_philo);
    printf(HBLU"[Time to burnout]:"HYEL" %d\n", param.ttb);
    printf(HBLU"[Time to compile]:"HYEL" %d\n", param.ttc);
    printf(HBLU"[Time to debug]:"HYEL" %d\n", param.ttd);
    printf(HBLU"[Time to refactor]:"HYEL" %d\n", param.ttr);
    printf(HBLU"[Number of compiles required]:"HYEL" %d\n", param.ncr);
    printf(HBLU"[Dongle cooldown]:"HYEL" %d\n", param.dc);
    printf(HBLU"[scheduler]: "HYEL);
    if (param.scheduler == FIFO)
        printf("fifo\n"CRESET);
    else if (param.scheduler == EDF)
        printf("edf\n"CRESET);
}