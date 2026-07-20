/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/20 23:09:42 by cebouhad         ###   ########.fr       */
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
#include <sys/time.h>
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

typedef         pthread_mutex_t t_mutex;
typedef  struct timespec        timespec_t;


typedef struct s_params
{
    size_t  coder;
    size_t  ttb;
    size_t  ttc;
    size_t  ttd;
    size_t  ttr;
    size_t  dc;
    int     ncr;
    int     scheduler;

} t_params;

typedef struct s_global_mutex
{
    t_mutex     display_f;
    t_mutex     timestamp_f;
    t_mutex     *dongles;
    t_mutex     *timestamp_data;

} t_global_mutex;

typedef struct s_coder_mutex
{
    t_mutex     *display;
    t_mutex     *dongles;
    t_mutex     *timestamp_data;
    t_mutex     *timestamp_update;

} t_coder_mutex;

typedef struct s_coder
{
    int             id;
    clock_t         *timestamps;
    t_params        params;
    timespec_t      start;
    t_coder_mutex   coder_mutex;
    
} t_coder;

typedef struct  s_monitoring
{
    int        ttb;
    int        nb_coder;
    clock_t    *timestamps_arr;
    t_mutex    *timestamp_data;
    t_mutex    *timestamp_f;
    
} t_monitoring;



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

/* init */
int     init_monitoring(t_monitoring  *monitoring, t_params params, t_global_mutex *gmu);
t_coder **init_coder(t_params *params, t_mutex *dongles, t_mutex *dashboard_mu, time_t *dashboard);
void    *destroy_coders(t_coder ***coders, int idx);

/* display */
void    display_mutex_data(t_global_mutex mu, size_t coders);
void    display_params(t_params param);
void    display_coder(t_coder coder);
void    display_coders(t_coder **coders);
void    safe_print(t_coder coder, int action);
void    display_monitoring_dashboard(time_t *dashboard, int coders);

/* utils */

size_t  get_str_arr_len(char **str_arr);
int     get_dongle(int id, int number_of_coder, int type);
int     ft_is_digit(char c);
void    ft_memcopy(void *src, void *dst, unsigned long size);

/* thread */

void    *coder_thread(void *data);
void    *monitoring_thread(void *data);
int     thead_luncher(t_params *param, t_mutex *dongles, t_mutex *dashboard_mu);

/* mutex */
int clean_gmutex(t_global_mutex *mu, size_t coders);
int g_mutex_initialisation(t_global_mutex  *gmutex, size_t coders);

/* time */

struct timespec time_diff(struct timespec start, struct timespec end);
clock_t         time_calculation(struct timespec time);

#endif