/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:56:23 by agallet           #+#    #+#             */
/*   Updated: 2023/08/26 10:34:40 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	write_smth(char *str, t_thread_t *p)
{
	long int	time;

	time = 0;
	time = get_time() - p->arg->t_start;
	if (!check_death(p, 0))
		printf("%ld %d %s\n", time, p->id, str);
}

void	ft_sleep(long int time, t_thread_t *data)
{
	long int	time_start;

	time_start = 0;
	time_start = get_time();
	while (!check_death(data, 0)
		&& get_time() - time_start < time)
		usleep(time / 5);
}

void	clear_data(t_all_t *data)
{
	free(data->arg);
	free(data->thread);
}

int	main(int argc, char **argv)
{
	t_all_t		test;
	int			i;

	i = 0;
	if (init(&test, argc, argv))
		return (1);
	test.arg->t_start = get_time();
	while (i < test.arg->n_philo)
	{
		test.thread[i].id = i + 1;
		pthread_create(&test.thread[i].pthread_id, NULL,
			&routine, &test.thread[i]);
		i++;
	}
	i = 0;
	while (i < test.arg->n_philo)
	{
		pthread_detach(test.thread[i].pthread_id);
		i++;
	}
	r_death(&test);
	return (0);
}
