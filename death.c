/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:17:13 by agallet           #+#    #+#             */
/*   Updated: 2023/08/26 10:34:05 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_thread_t *data, int s)
{
	pthread_mutex_lock(&data->arg->dead);
	if (s && !data->arg->finish)
	{
		data->arg->finish = 1;
	}
	if (data->arg->finish)
	{
		pthread_mutex_unlock(&data->arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->arg->dead);
	return (0);
}

void	r_death1(t_all_t *p, int *index, int *all)
{
	if (*all == p->arg->n_philo)
	{
		pthread_mutex_lock(&p->arg->write);
		write_smth("all_meal ok", &p->thread[*index]);
		pthread_mutex_unlock(&p->arg->write);
	}
	else
	{
		pthread_mutex_lock(&p->arg->write);
		write_smth("is died", &p->thread[*index]);
		pthread_mutex_unlock(&p->arg->write);
	}
	check_death(&p->thread[*index], 1);
}

void	r_death(t_all_t *p)
{
	int		i;
	int		all_eating;

	i = 0;
	all_eating = 0;
	while (!check_death(&p->thread[i], 0))
	{	
		if (!check_death(&p->thread[i], 0)
			&& (get_time() - get_ms_eat(&p->thread[i]))
			> (long)(p->arg->t_to_die))
			break ;
		if (p->arg->n_time_eat
			&& get_n_eat(&p->thread[i]) == p->arg->n_time_eat)
			all_eating++;
		if (all_eating == p->arg->n_philo)
			break ;
		i++;
		if (i == p->arg->n_philo)
		{
			all_eating = 0;
			i = 0;
		}
		usleep(100);
	}
	r_death1(p, &i, &all_eating);
}
