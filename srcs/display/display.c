/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/31 15:44:54 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"



void safe_print(t_coder coder, int action)
{
    clock_t timestamp;
    struct timespec tm;
    
    pthread_mutex_lock(coder.coder_mutex.display_f);
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
    pthread_mutex_unlock(coder.coder_mutex.display_f);
}

static void display_coder(t_coder *coder)
{
    printf("Coder: %d\n", coder->id);
    printf("last compilation : %ld\n", *(coder->last_compilation));
    printf("Usb left: %p last use %ld\n", coder->coder_mutex.dongle_l.dongle, coder->coder_mutex.dongle_l.last_use);
    printf("Usb right: %p last use %ld\n", coder->coder_mutex.dongle_r.dongle, coder->coder_mutex.dongle_r.last_use);
    printf("display mutex %p\n", coder->coder_mutex.display_f);
    printf("timestamp_f mutex %p\n", coder->coder_mutex.timestamp_f);
    printf("cond left %p\n", &coder->cond_left);
    printf("cond left %p\n", &coder->cond_right);
}

void display_coders(t_coder *coders, int nb_coder)
{
    int i;

    i = 0;
    printf("\n"HGRN"[ DISPLAY CODERS INFORMATIONS ]"CRESET"\n\n");
    while (i < nb_coder)
    {
        display_coder(&coders[i]);
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

void display_mutex_data(int nb_coder, t_global_mutex global_mu)
{
    int i;

    printf("display fonction mutex: %p\n", &global_mu.display_f);
    printf("timestamp fonction mutex: %p\n", &global_mu.timestamp_f);
    i = 0;
    while (i < nb_coder)
    {
        printf("Dongle [%d] %p\n", i, &global_mu.dongles[i]);
        i++;
    }
        
}

void display_request(t_request request)
{
    printf("\nRequest Id: %d\n",request.request_id);
    printf("Coder Id: %d\n",request.coder_id);
    printf("Last compilation: %ld\n",request.last_compilation);
    // printf("Cond adresse %p\n", request.cond);
    // printf("Children left: %p\n", request.left);
    // printf("Children right: %p\n", request.right);
}

void display_tree(t_request *root)
{
    if(!root)
        return;

    display_request(*root);
    display_tree(root->left);
    display_tree(root->right);
}