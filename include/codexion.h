/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/28 01:09:18 by cdric.b          ###   ########.fr       */
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
#define OFF 0
#define ON 1
#define CODER_MAX 200
#define PARAMS_SIZE 8



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
    STATE,
    STATE_MUTEX,
    TIMESTAMPS,
    TIMESTAMPS_MUTEX,
    CODER_MUTEX,
    CODER_COND,
    COUNTER,
    COUNTER_MU
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

typedef struct s_simulation
{
    int             params[8];
    int             simulation_state;
    pthread_mutex_t sim_state_mutex;
    t_dongle        *dongles;
    clock_t         *timestamp;
    pthread_mutex_t *timestamp_mutext;
    pthread_mutex_t display_mutex;
    
} t_simulation;


typedef struct s_coder
{
    int             params[8];
    clock_t         start;
    int             compilation_counter;
    pthread_mutex_t *compilation_counter_mutex;
    t_simulation   *simulation_data;
    t_dongle        *dongles_left;
    t_dongle        *dongles_right;
    clock_t         *timestamp;
    pthread_mutex_t *timestamp_mutex;
    pthread_mutex_t *display_mu;
    
} t_coder;


/* error */
int     msg_error(int code);
void    ft_putnbr_error(int fd, int nb, int base);
/* parsing */

int parse_arguments(char **args, int params[8]);
int parsing_error_msg(int code, char *arg);

/* init */

int clean_simulation(t_simulation *sim, int code);
int init_simulation(int params[8], t_simulation *sim);

/* utils 1 */
void    *init_dyn_arr(int nb, int size);
int     ft_is_digit(char c);
size_t  get_str_arr_len(char **str_arr);
void	ft_memcopy(void *src, void *dst, unsigned long size);

/* utils 2 */

pthread_t       *init_threads(int nb);
clock_t         *init_clock(int nb);
pthread_mutex_t *init_mutex(int nb);
pthread_cond_t  *init_cond(int nb);
int             clean_dynamique_cond(pthread_cond_t *cond, int nb);
int             clean_dynamique_mutex(pthread_mutex_t *mutex, int nb);

/* dongle managment */

void        *clean_dongles(t_dongle *dongles, int idx);
t_dongle    *dongles_initialisation(int nb_coder);

/* display */
void display_dongles_data(t_dongle *dongles, int nb_dongle);
void display_params(int params[8], int nb);


/* thread */



/* simulation utils*/

int     check_simulation_state(t_simulation *sim, int state);
void    set_simulation_state(t_simulation *sim, int state);
int     get_param(t_simulation *sim, int param);
void    safe_printf(t_simulation *sim, char *msg);

/* time */

clock_t time_calculation(struct timespec time);
long    nano_to_ms(long nano);

#endif