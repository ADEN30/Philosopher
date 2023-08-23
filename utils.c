/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:07:58 by agallet           #+#    #+#             */
/*   Updated: 2023/08/23 18:17:28 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_time(void)
{
	long int		time_start;
	struct timeval	current_time;

	time_start = 0;
	gettimeofday(&current_time, NULL);
	time_start = current_time.tv_sec * 1000
		+ current_time.tv_usec / 1000 ;
	return (time_start);
}

void	write_smth(char *str, t_thread_t *p)
{
	long int	time;

	time = 0;
	time = get_time() - p->arg->t_start;
	if (!check_death(p, 0))
		printf("%ld %d %s\n", time, p->id, str);
}

long int	get_ms_eat(t_thread_t *p)
{
	long int	eat;

	pthread_mutex_lock(&p->arg->get_time_eat);
	eat = p->ms_eat;
	pthread_mutex_unlock(&p->arg->get_time_eat);
	return (eat);
}

int	get_n_eat(t_thread_t *p)
{
	int	eat;

	pthread_mutex_lock(&p->arg->get_n_eat);
	eat = p->n_eat;
	pthread_mutex_unlock(&p->arg->get_n_eat);
	return (eat);
}

void	set_n_eat(t_thread_t *p)
{
	pthread_mutex_lock(&p->arg->get_n_eat);
	p->n_eat++;;
	pthread_mutex_unlock(&p->arg->get_n_eat);
}

void	set_ms_eat(t_thread_t *p)
{
	pthread_mutex_lock(&p->arg->get_time_eat);
	p->ms_eat = get_time();
	set_n_eat(p);
	pthread_mutex_unlock(&p->arg->get_time_eat);
}

void	ft_sleep(long int time, t_thread_t *data)
{
	long int	time_start;

	time_start = 0;
	time_start = get_time();
	while (!check_death(data, 0)
		&& get_time() - time_start < time)
		usleep(time / 10);
}
