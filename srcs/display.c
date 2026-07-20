/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 07:38:54 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void safe_print(t_coder coder, int action)
{
    mutex_t print_mutex;
    struct timeval timestamp;
    time_t now;
    memset(&print_mutex, 0, sizeof(mutex_t));
    pthread_mutex_lock(&print_mutex);

    gettimeofday(&timestamp, NULL);
    now = (timestamp.tv_usec - coder.start) / 1000;
    if (action == TAKE)
    {
        printf(HCYN"%ld %d has taken a dongle"CRESET"\n",now,coder.id);
        printf(HCYN"%ld %d has taken a dongle"CRESET"\n",now, coder.id);
    }
    if (action == COMPILE)
        printf(HCYN"%ld %d is compiling"CRESET"\n",now,coder.id);
    if (action == DEBBUG)
        printf(HCYN"%ld %d is debugging"CRESET"\n", now, coder.id);
    if (action == REFACTO)
        printf(HCYN"%ld %d is refactoring"CRESET"\n", now, coder.id);
    pthread_mutex_unlock(&print_mutex);
    pthread_mutex_destroy(&print_mutex);
}

void display_coder(t_coder coder)
{
    printf("Coder: %d\n", coder.id);
    printf("Usb left: %p\n", coder.dongle_l);
    printf("Usb right: %p\n", coder.dongle_r);
    printf("dashboard mutex %p\n", coder.mutex_dashboard);
    printf("dashboard adress %p\n", coder.compilation_dashboard);
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

void display_monitoring_dashboard(time_t *dashboard, int coders)
{
    int i;

    i = 0;
    printf("Nombre de coder %d\n", coders);
    while (i < coders)
    {
        printf("Coder %d last compilation %ld\n", i, dashboard[i]);
        i++;
    }
}