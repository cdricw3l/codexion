/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/27 08:26:39 by cebouhad         ###   ########.fr       */
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

void safe_print(t_coder coder, int action)
{
    clock_t timestamp;
    struct timespec tm;
    
    pthread_mutex_lock(coder.coder_mutex->display_f);
    clock_gettime(CLOCK_MONOTONIC, &tm);
    timestamp = time_calculation(time_diff(coder.start, tm));
    if (action == TAKE)
        printf(HCYN"%ld %d has taken a dongle"CRESET"\n",timestamp, coder.id);
    if (action == COMPILE)
        printf(HCYN"%ld %d is compiling"CRESET"\n",timestamp, coder.id);
    if (action == DEBBUG)
        printf(HCYN"%ld %d is debugging"CRESET"\n",timestamp, coder.id);
    if (action == REFACTO)
        printf(HCYN"%ld %d is refactoring"CRESET"\n",timestamp, coder.id);
    pthread_mutex_unlock(coder.coder_mutex->display_f);
}

static void display_coder(t_coder coder)
{
    printf("Coder: %d\n", coder.id);
    printf("Usb left: %p\n", coder.coder_mutex->dongles_l);
    printf("Usb right: %p\n", coder.coder_mutex->dongles_r);
    printf("display mutex %p\n", coder.coder_mutex->display_f);
    printf("timestamp field %p\n", coder.timestamps);
    printf("timestamp_f mutex %p\n", coder.coder_mutex->m_timestamp_f);
    printf("timestamp data mutex %p\n", coder.coder_mutex->m_timestamp_data);
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

void display_params(int params[8])
{
    printf(BHGRN"Program settings:\n");
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