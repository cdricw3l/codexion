/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:02:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 19:25:44 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <time.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/time.h>
# include "color_codes.h"

# define FALSE 0
# define TRUE 1
# define ERR -1
# define FIFO 0
# define EDF 1
# define LEFT 0
# define RIGHT 1
# define TIMESTAMP_DONGLE 0
# define TIMESTAMP_COMPILATION 1
# define ON 0
# define OFF 1


enum e_PARAMS
{
	nbc,
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
	BAD_ARG,
	MUTEX_ERR,
	QUEUE_ERR,
	THREAD_CREATION_ERR,
	THREAD_JOINT_ERR,
};

typedef enum e_actions
{
	TAKE,
	RELEASE,
	COMPILE,
	DEBBUG,
	REFACTO,
	DEAD
}	t_actions;

/* philo max is defined by: cat /proc/sys/kernel/threads-max */

typedef struct timespec	t_timespec;

typedef struct s_dongle
{
	clock_t			last_use;
	pthread_mutex_t	*dongle;

}	t_dongle;

typedef struct s_request
{
	int					coder_id;
	int					request_id;
	int					ttb;
	clock_t				last_compilation;
	pthread_cond_t		*cond;
	pthread_mutex_t		*mu;
	struct s_request	*left;
	struct s_request	*right;

}	t_request;

typedef struct s_queue
{
	int				request_counter;
	int				queue_type;
	int				ttb;
	size_t			size;
	t_request		**request_queue;
	pthread_cond_t	cond;
	pthread_mutex_t	queue_lock;

}	t_queue;

typedef struct s_global_mutex
{
	pthread_mutex_t	display_f;
	pthread_mutex_t	timestamp_f;
	pthread_mutex_t	*dongles;
	pthread_mutex_t	*state;


}	t_global_mutex;

typedef struct s_coder_mutex
{
	pthread_mutex_t	*display_f;
	pthread_mutex_t	*state;
	pthread_mutex_t	*timestamp_f;
	pthread_mutex_t	*can_compile_mu;
	t_dongle		dongle_l;
	t_dongle		dongle_r;

}	t_coder_mutex;

typedef struct s_coder
{
	int				id;
	int				state;
	int				nb_of_compil;
	int				params[8];
	t_timespec		start;
	clock_t			*last_compilation;
	t_queue			*queue;
	t_coder_mutex	coder_mutex;
	pthread_cond_t *can_compile_cond;
	int 			*can_compile;

}	t_coder;

typedef struct s_monitoring
{
	int				nb_coder;
	int				params[8];
	t_coder			*coder;
	clock_t			*last_compilations;
	pthread_mutex_t	*display_f;
	pthread_mutex_t	*timestamp_f;
	pthread_mutex_t	*state;

}	t_monitoring;

typedef struct s_scheduler
{
	int 			nb_coder;
	int 			*can_compile;
	t_queue			*queue;
	pthread_mutex_t	*can_compile_mu;
	pthread_cond_t	*can_compile_co;
	t_coder			*coder;
	pthread_mutex_t	*state;
	int 			on_off;
	
} t_scheduler;

/* error */

int				error_msg(int code, char *arg);
void			*queue_err(int code);
/* parsing */

int				parse_arguments(int argc, char **args, int params[8]);

/* display */
void			display_params(int params[8]);
void			display_coders(t_coder *coders, int nb_coder);
void			safe_print(t_coder coder, int action, pthread_mutex_t *lock);
void			display_mutex_data(int nb_coder, t_global_mutex global_mu);
void			display_request(t_request request);

/* utils */
size_t			get_str_arr_len(char **str_arr);
int				get_dongle(int id, int number_of_coder, int type);
int				ft_is_digit(char c);
void			ft_memcopy(void *src, void *dst, unsigned long size);
int				max(int a, int b);

/* thread */
int				thread_launcher(t_scheduler *scheduler,
					t_coder *coders, t_monitoring *monitor, int nb_coder);
void			*monitor_routine(void *data);
void 			*scheduler_routine(void *data);
int				check_state(t_coder *coder);

/* coder */
void			*coder_routine(void *data);
void			compile(t_coder *coder);
void			debbug(t_coder *coder);
void			refactor(t_coder *coder);

/* initialisation */
int				mutex_init(int nb_coder, t_global_mutex *global_mu);
t_monitoring	*monitoring_init(int *params,
					t_global_mutex *global_mu, t_coder *coder);
t_coder			*coders_init(int *params,
					t_global_mutex *global_mu, t_queue *queue, t_scheduler *schedul);
t_queue			*queue_init(int type, int ttb);
t_scheduler 	*scheduler_init(int nb_coder, t_queue *queue);

/* clean */
int				clean(int nb_coder,
					t_coder *coders,
					t_global_mutex *global_mu, t_queue *queue);

/* time */
long			second_to_nano(long sec);
long			ms_to_nano(long ms);
long			nano_to_ms(long nano);
void			set_timestamp(t_coder *coder, int type);
clock_t			time_calculation(struct timespec time);
struct timespec	time_diff(struct timespec start, struct timespec end);
struct timespec	futuristic_timespec(int ms);

/* tree */
int				tree_height(t_request *root);
int				count_tree_node(t_request *root, int size);
void			display_tree(t_request *root);

/* heap queue */
int				push_request(t_queue *request_queue, t_request *request);
int				pop_request(t_queue *request_queue);
int				can_compile(t_coder *coder);
void			pop(t_request **queue, int queue_size);
void			push(t_request **queue, t_request *node);
void			swap_request(t_request **r1, t_request **r2);
void			add_request(t_request **arr, size_t queue_size, int queue_type);
void			plug_heap_nodes(t_request **arr, size_t queue_size);
t_request		**bfs_binary_tree_as_arr(t_queue *request_queue);

/* request */
int				create_and_send_request(t_coder *coder);
t_request		*create_request(t_coder *coder);

#endif