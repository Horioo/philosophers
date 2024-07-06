/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:37 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/05/14 16:41:09 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

// ./philo 5 800 200 200 [5]
// ./phile nbr_philo time_to_die time_to_eat time_to_sleep [nbr_of_meals_eaten]
// Se o time to die for maior que 
// 2(Time_to_eat ou time_to_sleep)(Pares) 
// 3(Time_to_eat ou time_to_sleep)(Impares)

typedef pthread_mutex_t		t_mtx;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;
typedef struct s_table		t_table;
typedef enum e_opcode		t_opcode;
typedef enum e_time_code	t_time_code;
typedef enum e_philo_status	t_philo_status;

# define RST  	"\x1B[0m"
# define R     	"\x1B[1;31m"
# define G   	"\x1B[1;32m"
# define Y      "\033[1;33m"   
# define B      "\033[1;34m"   
# define M      "\033[1;35m"   
# define C      "\033[1;36m"   
# define W      "\033[1;37m"
# define DEBUG_MODE 0

enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
};

enum e_time_code
{
	MILLISECONDS,
	MICROSECONDS,
};

enum	e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
};

struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
};

struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
};

struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_sim;
	bool		end_sim;
	bool		all_threads_ready;
	long		nbr_threads_running;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
};

/* Dinner */

void	thinking(t_philo *philo, bool pre_sim);
void	dinner_start(t_table *table);

/* Get Set */

long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	simulation_finished(t_table *table);

/* Init */

void	table_init(t_table *table);

/* Monitor */

void	*monitor_dinner(void *data);

/* Parsing */

int		parsing(t_table *table, char **av);

/* Safe_Funcs */

void	*safe_malloc(size_t bytes);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex(t_mtx *mutex, t_opcode opcode);

/* Synchro */

void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr);
void	increment_long(t_mtx *mtx, long *value);
void	dsynchronize_philos(t_philo *philo);

/* Utils */

long	gettime(t_time_code time_code);
void	error_exit(char *error);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

/* Write */

void	write_status(t_philo_status status, t_philo *philo, bool debug);

#endif