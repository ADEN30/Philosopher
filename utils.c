/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:07:58 by agallet           #+#    #+#             */
/*   Updated: 2023/08/25 12:02:29 by agallet          ###   ########.fr       */
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
	p->n_eat = p->n_eat + 1;
	pthread_mutex_unlock(&p->arg->get_n_eat);
}

void	set_ms_eat(t_thread_t *p)
{
	pthread_mutex_lock(&p->arg->get_time_eat);
	p->ms_eat = get_time();
	pthread_mutex_unlock(&p->arg->get_time_eat);
}
