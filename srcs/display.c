/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/18 09:12:42 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void safe_print(t_coder coder, int action)
{
    mutex print_mutex;

    pthread_mutex_lock(&print_mutex);
    if (action == TAKE)
    {
        printf(HCYN"%d has taken a dongle"CRESET"\n", coder.id);
        printf(HCYN"%d has taken a dongle"CRESET"\n", coder.id);
    }
    if (action == COMPILE)
        printf(HCYN"%d is compiling"CRESET"\n", coder.id);
    if (action == DEBBUG)
        printf(HCYN"%d is debugging"CRESET"\n", coder.id);
    if (action == REFACTO)
        printf(HCYN"%d is refactoring"CRESET"\n", coder.id);
    pthread_mutex_unlock(&print_mutex);
}

void display_coder(t_coder coder)
{
    printf("Coder: %d\n", coder.id);
    printf("Usb left: %p\n", coder.dongle_l);
    printf("Usb right: %p\n", coder.dongle_r);
    printf("dashboard adress %p\n", coder.last_compile);
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
    printf(HBLU"[Number of compiles required]:"HYEL" %d\n", param.ncr);
    printf(HBLU"[Dongle cooldown]:"HYEL" %zu ms\n", param.dc);
    printf(HBLU"[scheduler]: "HYEL);
    if (param.scheduler == FIFO)
        printf("edf"CRESET"\n");
    else if (param.scheduler == EDF)
        printf("edf"CRESET"\n");
}