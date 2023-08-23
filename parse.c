/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:16:21 by agallet           #+#    #+#             */
/*   Updated: 2023/08/23 16:16:26 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	nb;
	int		negatif;

	i = 0;
	nb = 0;
	negatif = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negatif *= -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * negatif);
}

void	arg_set(t_arg_t *arg, int nb)
{
	static int	i;

	if (i == 0)
		arg->n_philo = nb;
	else if (i == 1)
		arg->t_to_die = nb;
	else if (i == 2)
		arg->t_to_eat = nb;
	else if (i == 3)
		arg->t_to_sleep = nb;
	else if (i == 4)
		arg->n_time_eat = nb;
	arg->finish = 0;
	i++;
}

t_arg_t	*init_arg(char **argv)
{
	int		i;
	t_arg_t	*arg;

	i = 1;
	arg = malloc(sizeof(t_arg_t));
	if (!arg)
		return (NULL);
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 0)
			return (NULL);
		else
			arg_set(arg, ft_atoi(argv[i]));
		i++;
	}
	return (arg);
}
