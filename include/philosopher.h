#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct t_arg
{

	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	long int		n_time_eat;
	pthread_mutex_t	dead;
} t_arg_t;


typedef struct t_thread
{
	int	id;
	int	pthread_id;
	int	pthread_death_id;
	pthread_mutex_t	r_mutex;
	pthread_mutex_t	l_mutex;
	t_arg_t			r_arg;
	t_arg_t			l_arg;
	long int		ms_eat;
	unsigned int	n_eat;
}	t_thread_t;

typedef struct	t_all
{
	t_thread_t	*thread;
	t_arg_t		*arg;
}	t_all_t;

#endif
