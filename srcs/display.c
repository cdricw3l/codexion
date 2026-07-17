/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/17 12:44:25 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void display_coder(t_coder coder)
{
    printf("Coder: %d\n", coder.id);
    printf("Usb left: %p\n", &coder.dongle_l);
    printf("Usb right: %p\n", &coder.dongle_r);
}

void display_coders(t_coder **coders)
{
    size_t i;

    i = 0;
    printf("\n"HGRN"[ DISPLAY CODERS INFORMATIONS ]"CRESET"\n\n");
    while (coders[i])
    {
        display_coder(*coders[i]);
        printf("\n");
        i++;
    }
}

void display_params(t_params param)
{
    printf(BHGRN"Program settings:\n");
    printf(HBLU"[Number of philosopher]:"HYEL" %zu\n", param.coder);
    printf(HBLU"[Time to burnout]:"HYEL" %zu ms\n", param.ttb);
    printf(HBLU"[Time to compile]:"HYEL" %zu ms\n", param.ttc);
    printf(HBLU"[Time to debug]:"HYEL" %zu ms\n", param.ttd);
    printf(HBLU"[Time to refactor]:"HYEL" %zu ms\n", param.ttr);
    printf(HBLU"[Number of compiles required]:"HYEL" %zu\n", param.ncr);
    printf(HBLU"[Dongle cooldown]:"HYEL" %zu ms\n", param.dc);
    printf(HBLU"[scheduler]: "HYEL);
    if (param.scheduler == FIFO)
        printf("edf"CRESET"\n");
    else if (param.scheduler == EDF)
        printf("edf"CRESET"\n");
}