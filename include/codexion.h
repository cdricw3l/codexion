/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/18 09:05:48 by cdric.b          ###   ########.fr       */
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
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include "color-codes.h"

#define FALSE 0
#define TRUE 1
#define FIFO 0
#define EDF 1
#define LEFT 0
#define RIGHT 1

/* action */


typedef enum e_actions
{
    TAKE,
    RELEASE,
    COMPILE,
    DEBBUG,
    REFACTO

} t_actions;

/* philo max is defined by: cat /proc/sys/kernel/threads-max */
#define CODER_MAX 124441

typedef pthread_mutex_t mutex;


typedef struct s_params
{
    size_t coder;
    size_t ttb;
    size_t ttc;
    size_t ttd;
    size_t ttr;
    int     ncr;
    size_t dc;
    int scheduler;

} t_params;

typedef struct s_monitor
{
    

} t_monitor;



typedef struct s_coder
{
    int             id;
    int             *last_compile;
    pthread_mutex_t *dongle_l;
    pthread_mutex_t *dongle_r;
    t_params        param;
    
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

enum e_PARSING_ERROR
{
    NB_ARG,
    BAD_ARG
};

/* error */

int     mutex_initialisation_error();
int     parsing_error_msg(int code, char *arg);

/* parsing */

int     parse_arguments(char **args, t_params *params);

/* display */

void    display_params(t_params param);
void    display_coder(t_coder coder);
void    display_coders(t_coder **coders);
void    safe_print(t_coder coder, int action);
/* utils */

size_t  get_str_arr_len(char **str_arr);
int get_dongle(int id, int number_of_coder, int type);
int     ft_is_digit(char c);
void    ft_memcopy(void *src, void *dst, unsigned long size);

/* thread */

int     thead_luncher(t_params *param, mutex **dongles);
mutex   *mutex_initialisation(size_t nb_coder);

/* time */

void update_timestamps(int *dashboard);

#endif