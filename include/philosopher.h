#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct t_arg
{

	long int	n_philo;
	long int	t_to_die;
	long int	t_to_eat;
	long int	t_to_sleep;
	long int	n_time_eat;
} t_arg_t;

#endif
