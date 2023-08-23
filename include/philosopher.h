/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:27:14 by agallet           #+#    #+#             */
/*   Updated: 2023/08/23 18:16:39 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct t_arg
{
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	long int		n_time_eat;
	long int		t_start;
	long int		time;
	pthread_t		pthread_death_id;
	pthread_mutex_t	dead;
	pthread_mutex_t	get_time_eat;
	pthread_mutex_t	get_n_eat;
	pthread_mutex_t	write;
	int				finish;
}	t_arg_t;

typedef struct t_thread
{
	int				id;
	pthread_t		pthread_id;
	pthread_mutex_t	*r_mutex;
	pthread_mutex_t	l_mutex;
	t_arg_t			*arg;
	long int		ms_eat;
	unsigned int	n_eat;
}	t_thread_t;

typedef struct t_all
{
	t_thread_t	*thread;
	t_arg_t		*arg;
}	t_all_t;

void		r1(t_thread_t *p);
void		r0(t_thread_t *p);
void		*routine(void *data);

int			check_death(t_thread_t *data, int s);
void		r_death1(t_all_t *p, int *index, int *all);
void		r_death(t_all_t *p);

int			ft_atoi(const char *str);
void		arg_set(t_arg_t *arg, int nb);
t_arg_t		*init_arg(char **argv);

long int	get_time(void);
void		write_smth(char *str, t_thread_t *p);
long int	get_ms_eat(t_thread_t *p);
int			get_n_eat(t_thread_t *p);
void		set_n_eat(t_thread_t *p);
void		set_ms_eat(t_thread_t *p);
void		ft_sleep(long int time, t_thread_t *data);

int			init(t_all_t *data, int argc, char **argv);
long int	get_time(void);
int			check_death(t_thread_t *data, int s);
#endif
