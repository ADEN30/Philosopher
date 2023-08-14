#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct t_arg
{

	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	long int		n_time_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	get_time_eat;
	int				finish;
} t_arg_t;


typedef struct t_thread
{
	int	id;
	pthread_t	pthread_id;
	pthread_t	pthread_death_id;
	pthread_mutex_t	r_mutex;
	pthread_mutex_t	l_mutex;
	t_arg_t			*arg;
	long int		ms_eat;
	unsigned int	n_eat;
}	t_thread_t;

typedef struct	t_all
{
	t_thread_t	*thread;
	t_arg_t		*arg;
}	t_all_t;

int	init(t_all_t *data, int argc, char **argv);
t_arg_t	*init_arg(char **argv);
#endif
