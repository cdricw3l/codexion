/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:45:50 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/10 15:18:58 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void display_params(int params[8], int nb)
{
    printf(BHGRN"Program settings: %d\n", nb);
    printf(HBLU"[Number of philosopher]:"HYEL" %d\n", params[number_of_coders]);
    printf(HBLU"[Time to burnout]:"HYEL" %d ms\n", params[time_to_burnout]);
    printf(HBLU"[Time to compile]:"HYEL" %d ms\n", params[time_to_compile]);
    printf(HBLU"[Time to debug]:"HYEL" %d ms\n", params[time_to_debug]);
    printf(HBLU"[Time to refactor]:"HYEL" %d ms\n", params[time_to_refactor]);
    printf(HBLU"[Number of compiles required]:"HYEL" %d\n", params[number_of_compiles_required]);
    printf(HBLU"[Dongle cooldown]:"HYEL" %d ms\n", params[dongle_cooldown]);
    printf(HBLU"[scheduler]: "HYEL);
    if (params[scheduler] == FIFO)
        printf("fifo"CRESET"\n");
    else if (params[scheduler] == EDF)
        printf("edf"CRESET"\n");
    printf("\n");
}

void display_dongles_data(t_dongle *dongles, int nb_dongle)
{
    int i;

    if(!dongles)
        return ;
    i = 0;
    while (i < nb_dongle)
    {
        printf("Dongle id: %d\n", dongles[i].dongle_id);
        printf("Dongle Last use: %lu\n", dongles[i].last_use);
        printf("Queue size: %d\n", dongles[i].queue_size);
        printf("Queue adresse: %p\n",dongles[i].queue);
        printf("Queue value: %p\n", *(dongles[i].queue));
        printf("Queue mutex: %p\n\n", &dongles[i].mu_dongle);
        i++;
    }
}