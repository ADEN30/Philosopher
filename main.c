#include "philosopher.h"

void	*routine(void *data)
{
	t_thread_t	*p;

	p = (t_thread_t*)data;
	if (p->id % 2 != 0)
		printf("Test from thread1\n");
	else
		printf("Test from thread2\n");
	return (0);
}

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

int	main(int argc, char **argv)
{
	t_all_t		test;
	int			i;

	i = 0;
	if (init(&test, argc, argv))
			return (1);
	while (i < test.arg->n_philo)
	{
		test.thread[i].id = i;
		pthread_create(&test.thread[i].pthread_id, NULL, &routine, &test.thread[i]);
		i++;
	}
	i = 0;
	while (i < test.arg->n_philo)
	{
		pthread_mutex_destroy(&test.thread[i].r_mutex);
		pthread_join(test.thread[i].pthread_id, NULL);
		i++;
	}
	printf("%d\n", test.arg->n_philo);
	return (0);
}
