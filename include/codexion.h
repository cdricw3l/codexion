/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 01:51:15 by cebouhad         ###   ########.fr       */
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

/* philo max is defined by: cat /proc/sys/kernel/threads-max */

typedef         struct timespec         timespec_t;

typedef struct s_dongle
{
    clock_t         last_use;
    pthread_mutex_t *dongle;

} t_dongle;

typedef struct s_request
{
    int                 coder_id;
    int                 request_id;
    int                 ttb;
    clock_t             last_compilation;
    pthread_cond_t      *cond;
    pthread_mutex_t     *mu;
    struct s_request    *left;
    struct s_request    *right;

} t_request;


typedef struct s_queue
{
    int             request_counter;
    int             queue_type;
    int             ttb;
    size_t          size;
    t_request       **request_queue;
    pthread_cond_t  cond;
    pthread_mutex_t queue_lock;

} t_queue;

typedef struct s_global_mutex
{
    pthread_mutex_t display_f;
    pthread_mutex_t timestamp_f;
    pthread_mutex_t *dongles;
    pthread_mutex_t *state;

    
} t_global_mutex;

typedef struct s_coder_mutex
{
    pthread_mutex_t *display_f;
    pthread_mutex_t *state;
    pthread_mutex_t *timestamp_f;
    t_dongle        dongle_l;
    t_dongle        dongle_r;
    
} t_coder_mutex;

typedef struct s_coder
{
    int             id;
    int             state;
    int             nb_of_compil;
    int             params[8];
    timespec_t      start;
    clock_t         *last_compilation;
    t_queue         *queue;
    pthread_t       thread;
    t_coder_mutex   coder_mutex;
} t_coder;


typedef struct s_monitoring
{
    t_coder         *coder;
    clock_t         *last_compilations;
    pthread_mutex_t *display_f;
    pthread_mutex_t *timestamp_f;
    pthread_mutex_t *state;
    int             nb_coder;
    int             params[8];
} t_monitoring;




/* error */

int     mutex_initialisation_error();
int     parsing_error_msg(int code, char *arg);

/* parsing */

int     parse_arguments(char **args, int params[8]);

/* init */


/* display */
void    display_params(int params[8]);
void    display_coders(t_coder *coders, int nb_coder);
void    safe_print(t_coder coder, int action, pthread_mutex_t *lock);
void    display_mutex_data(int nb_coder, t_global_mutex global_mu);
void    display_request(t_request request);

/* utils */
size_t  get_str_arr_len(char **str_arr);
int     get_dongle(int id, int number_of_coder, int type);
int     ft_is_digit(char c);
void    ft_memcopy(void *src, void *dst, unsigned long size);
int     max(int a, int b);


/* thread */
int     thread_launcher(t_coder *coder, t_monitoring *monitor, int nb_coder);
void    *monitor_routine(void *data);
    /* coder */
void    *coder_routine(void *data);
void	compile(t_coder *coder);
void	debbug(t_coder *coder);
void	refactor(t_coder *coder);

/* initialisation */

int         mutex_initialisation(int nb_coder, t_global_mutex *global_mu);
int         monitoring_initialisation(int *params, t_monitoring *monitoring, t_global_mutex *global_mu, t_coder *coder);
t_coder     *coders_initialisation(int *params, t_global_mutex *global_mu, t_queue *queue);
t_queue	    *queue_initialisation(int type, int ttb);

/* clean */

int mutex_destroy(int nb_coder, t_global_mutex *global_mu);
int clean_memory(int nb_coder, t_global_mutex *global_mu, t_monitoring *monitoring);
int clean_queue(t_queue *queue);

/* time */

long            second_to_nano(long sec);
long            ms_to_nano(long ms);
clock_t         time_calculation(struct timespec time);
struct timespec time_diff(struct timespec start, struct timespec end);
struct timespec futuristic_timespec(int ms);
long            nano_to_ms(long nano);
void            set_timestamp(t_coder *coder, int type);
/* tree */

int             tree_height(t_request *root);
int             count_tree_node(t_request *root, int size);
void            display_tree(t_request *root);

/* heap queue */

void	    pop(t_request **queue, int queue_size);
void	    push(t_request **queue, t_request *node);
void	    swap_request(t_request **r1, t_request **r2);
int         push_request(t_queue *request_queue, t_request *request);
int	        pop_request(t_queue *request_queue);
t_request   **bfs_binary_tree_as_arr(t_queue *request_queue);
void	    add_request(t_request **arr, size_t queue_size, int queue_type);
void	    plug_heap_nodes(t_request **arr, size_t queue_size);
int         can_compile(t_coder *coder);

/* request */

int         create_and_send_request(t_coder *coder);
t_request   *create_request(t_coder *coder);

#endif