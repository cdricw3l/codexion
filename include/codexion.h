/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/10 12:49:40 by cdric.b          ###   ########.fr       */
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
#include <malloc/malloc.h>
#include "color-codes.h"

#define FALSE 0
#define TRUE 1
#define ERR -1
#define FIFO 0
#define EDF 1
#define LEFT 0
#define RIGHT 1
#define TIMESTAMP_DONGLE 0
#define TIMESTAMP_COMPILATION 1

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

typedef enum e_actions
{
    TAKE,
    RELEASE,
    COMPILE,
    DEBBUG,
    REFACTO,
    DEAD

} t_actions;

enum e_error_init
{
    CODER,
    TIMESTAMPS,
    TIMESTAMPS_MUTEX,
    CODER_MUTEX,
    CODER_COND
};

/* philo max is defined by: cat /proc/sys/kernel/threads-max */

typedef         struct timespec         timespec_t;


typedef struct s_requests
{
    int id;
    struct s_queue_dongle *left;
    struct s_queue_dongle *right;
    
} t_requests;


typedef struct s_dongle
{
    int             dongle_id;
    int             queue_size;
    clock_t         last_use;
    t_requests      **queue;
    pthread_mutex_t mu_dongle;
    pthread_mutex_t mu_queue;

} t_dongle;

typedef struct  s_sim
{
    int             *params;
    pthread_t       *coders;
    pthread_t       monitor;
    pthread_t       scheduler;
    t_dongle        *dongles;
    clock_t         *timestamp;
    pthread_mutex_t *timestamp_mu;
    pthread_mutex_t display_mu;
    pthread_mutex_t  *coder_mu;
    pthread_cond_t  *coder_cond;
    
} t_sim;

/* error */
int msg_error(int code);

/* parsing */

int parse_arguments(char **args, int params[8]);
int parsing_error_msg(int code, char *arg);

/* utils */
int ft_is_digit(char c);
size_t get_str_arr_len(char **str_arr);

/* dongle managment */

void        *clean_dongles(t_dongle *dongles, int idx);
t_dongle    *dongles_initialisation(int nb_coder);

/* display */
void display_dongles_data(t_dongle *dongles, int nb_dongle);
void display_params(int params[8], int nb);

#endif