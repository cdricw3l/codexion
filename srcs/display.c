/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 11:53:45 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void safe_print(t_coder coder, int action)
{
    struct timespec timestamp;
    time_t now;
    
    pthread_mutex_lock(coder.mu_print);
    clock_gettime(CLOCK_MONOTONIC_RAW, &timestamp);

    now = time_diff(coder.start, timestamp.tv_nsec);
    if (action == TAKE)
    {
        printf(HCYN"start:%ld now:%ld result: %ld %d has taken a dongle"CRESET"\n",coder.start, timestamp.tv_nsec,now, coder.id);
        printf(HCYN"start:%ld now:%ld result: %ld %d has taken a dongle"CRESET"\n",coder.start, timestamp.tv_nsec,now, coder.id);
    }
    if (action == COMPILE)
        printf(HCYN"start:%ld now:%ld result: %ld %d is compiling"CRESET"\n",coder.start, timestamp.tv_nsec,now, coder.id);
    if (action == DEBBUG)
        printf(HCYN"start:%ld now:%ld result: %ld %d is debugging"CRESET"\n",coder.start, timestamp.tv_nsec,now, coder.id);
    if (action == REFACTO)
        printf(HCYN"start:%ld now:%ld result: %ld %d is refactoring"CRESET"\n",coder.start, timestamp.tv_nsec,now, coder.id);
    pthread_mutex_unlock(coder.mu_print);
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