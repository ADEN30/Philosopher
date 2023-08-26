/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:18:24 by agallet           #+#    #+#             */
/*   Updated: 2023/08/26 10:34:06 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	r1(t_thread_t *p)
{
	pthread_mutex_lock(&p->arg->write);
	write_smth("is sleeping", p);
	pthread_mutex_unlock(&p->arg->write);
	ft_sleep(p->arg->t_to_sleep, p);
	pthread_mutex_lock(&p->arg->write);
	write_smth("is thinking", p);
	pthread_mutex_unlock(&p->arg->write);
}

void	r0(t_thread_t *p)
{
	pthread_mutex_lock(&p->l_mutex);
	pthread_mutex_lock(&p->arg->write);
	write_smth("has taken a fork", p);
	pthread_mutex_unlock(&p->arg->write);
	pthread_mutex_lock(p->r_mutex);
	pthread_mutex_lock(&p->arg->write);
	write_smth("has taken a fork", p);
	pthread_mutex_unlock(&p->arg->write);
	pthread_mutex_lock(&p->arg->write);
	write_smth("is eating", p);
	pthread_mutex_unlock(&p->arg->write);
	set_ms_eat(p);
	ft_sleep(p->arg->t_to_eat, p);
	set_n_eat(p);
	pthread_mutex_unlock(p->r_mutex);
	pthread_mutex_unlock(&p->l_mutex);
	r1(p);
}

void	*routine(void *data)
{
	t_thread_t		*p;

	p = (t_thread_t *)data;
	if (p->id % 2 != 0)
	{
		ft_sleep(p->arg->t_to_die / p->arg->n_philo, p);
	}
	while (!check_death(p, 0))
		r0(p);
	return (0);
}
