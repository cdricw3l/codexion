/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 08:45:50 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/28 00:21:03 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

// void check_simulation_data(t_sim *simulation)
// {
//     int nb;
//     int i;
//     printf(HGRN">>>>>>> INITIALISATION DATA OK <<<<<<<"CRESET"\n");
//     nb = simulation->params[number_of_coders];
//     printf(HMAG">>>>>>> SIMULATION DATA ASSERTION CHECK <<<<<<<"CRESET"\n");
//     display_params(simulation->params, simulation->params[number_of_coders]);
//     i = 0;
//     assert(simulation->simulation_state == OFF);
//     assert(simulation);
//     printf("Simulation :"GRN"[OK]"CRESET"\n");
//     assert(simulation->coder_mu);
//     printf("Coder mutex :"GRN"[OK]"CRESET"\n");
//     assert(simulation->coder_state);
//     printf("Coder state :"GRN"[OK]"CRESET"\n");
//     assert(simulation->coder_state_mu);
//     printf("Coder state mutex :"GRN"[OK]"CRESET"\n");
//     assert(simulation->coders);
//     printf("Coder thread :"GRN"[OK]"CRESET"\n");
//     assert(simulation->coder_cond);
//     printf("Coder cond: "GRN"[OK]"CRESET"\n");
//     assert(&simulation->display_mu);
//     printf("Display mutex: "GRN"[OK]"CRESET"\n");
//     assert(simulation->dongles);
//     printf("Initialisation dongle: "GRN"[OK]"CRESET"\n");
//     assert(&simulation->monitor);
//     printf("Thread monitor: "GRN"[OK]"CRESET"\n");
//     assert(&simulation->scheduler);
//     printf("Thread scheduler: "GRN"[OK]"CRESET"\n");
//     assert(&simulation->simulation_mu);
//     printf("Mutext state simulation: "GRN"[OK]"CRESET"\n");
//     assert(simulation->simulation_state == OFF);
//     printf("Simulation state: "GRN"[OK]"CRESET"\n");
//     while (i < nb)
//     {
//         assert(&simulation->coders[i]);
//         printf("Coder thread %d :"GRN"[OK]"CRESET"\n", i);
//         assert(&simulation->coder_state[i] && simulation->coder_state[i] == OFF);
//         printf("Coder state %d :"GRN"[OK]"CRESET"\n", i);
//         assert(&simulation->coder_state_mu[i]);
//         printf("Coder state mutex %d :"GRN"[OK]"CRESET"\n", i);
//         assert(&simulation->coder_mu[i]);
//         printf("Coder mutex %d :"GRN"[OK]"CRESET"\n", i);
//         assert(&simulation->coder_cond[i]);
//         printf("Coder cond %d: "GRN"[OK]"CRESET"\n", i);
//         assert(&simulation->dongles[i]);
//          printf("Initialisation dongle %d: "GRN"[OK]"CRESET"\n", i);
//         i++;
//     }
//     printf(HGRN">>>>>>> SIMUALTION DATA CHECK OK <<<<<<<"CRESET"\n");

// }

void display_params(int params[8], int nb)
{
    printf(HBLU"[Number of philosopher]:"HYEL" %d\n", nb);
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