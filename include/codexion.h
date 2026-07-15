/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/15 18:20:49 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H


#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include "color-codes.h"

#define FALSE 0
#define TRUE 1
#define FIFO 0
#define EDF 1

/* philo max is defined by: cat /proc/sys/kernel/threads-max */
#define CODER_MAX 124441


typedef struct s_params
{
    int nb_philo;
    int ttb;
    int ttc;
    int ttd;
    int ttr;
    int ncr;
    int dc;
    int scheduler;

} t_params;


typedef struct s_coder
{
    int id;
    t_params *param;
    
} t_coder;

enum e_PARAMS
{
    number_of_coders,
    time_to_burnout,
    time_to_compile,
    time_to_debug,
    time_to_refactor,
    number_of_compiles_required,
    dongle_cooldown,
    scheduler
};

/* parsing */
int parse_arguments(char **args, t_params *params);

/* display */

void display_params(t_params param);

/* utils */
size_t get_str_arr_len(char **str_arr);
int ft_is_digit(char c);

/* thread */
int thead_luncher(t_params *param);
#endif