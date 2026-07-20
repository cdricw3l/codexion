/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/21 00:25:32 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void display_mutex_data(t_global_mutex mu, size_t coders)
{
    size_t i;

    printf("display fonction mutex %p\n", &mu.display_f);
    printf("timestamp fonction mutex %p\n", &mu.timestamp_f);
    if (mu.dongles)
    {
        i = 0;
        while (i < coders)
        {
            printf("Dongle [%ld] %p\n", i, &mu.dongles[i]);
            i++;
        }

    }
    if (mu.timestamp_data)
    {
        i = 0;
        while (i < coders)
        {
            printf("timestamp field [%ld] %p\n", i, &mu.timestamp_data[i]);
            i++;
        }
    }
}

// void safe_print(t_coder coder, int action)
// {
//     clock_t timestamp;
//     struct timespec tm;
    
//     pthread_mutex_lock(coder.mu_print);
//     clock_gettime(CLOCK_MONOTONIC, &tm);
//     timestamp = time_calculation(time_diff(coder.start, tm));
//     if (action == TAKE)
//         printf(HCYN"%ld %d has taken a dongle"CRESET"\n",timestamp, coder.id);
//     if (action == COMPILE)
//         printf(HCYN"%ld %d is compiling"CRESET"\n",timestamp, coder.id);
//     if (action == DEBBUG)
//         printf(HCYN"%ld %d is debugging"CRESET"\n",timestamp, coder.id);
//     if (action == REFACTO)
//         printf(HCYN"%ld %d is refactoring"CRESET"\n",timestamp, coder.id);
//     pthread_mutex_unlock(coder.mu_print);
// }

static void display_coder(t_coder coder)
{
    printf("Coder: %d\n", coder.id);
    printf("Usb left: %p\n", coder.coder_mutex->dongles_l);
    printf("Usb right: %p\n", coder.coder_mutex->dongles_r);
    printf("display mutex %p\n", coder.coder_mutex->display_f);
    printf("timestamp field %p\n", coder.timestamps);
    printf("timestamp_f mutex %p\n", coder.coder_mutex->m_timestamp_f);
    printf("timestamp data mutex %p\n", coder.coder_mutex->m_timestamp_data);
    display_params(coder.params);
}

void display_coders(t_coder *coders, size_t coder)
{
    size_t i;

    i = 0;
    printf("\n"HGRN"[ DISPLAY CODERS INFORMATIONS ]"CRESET"\n\n");
    while (i < coder)
    {
        display_coder(coders[i]);
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