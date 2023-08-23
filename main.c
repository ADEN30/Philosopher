/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:56:23 by agallet           #+#    #+#             */
/*   Updated: 2023/08/23 17:02:36 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		test.thread[i].id = i;
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
	clear_data(&test);
	return (0);
}
