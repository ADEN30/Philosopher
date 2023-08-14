#include "philosopher.h"


long int	get_time(void)
{
	long int	time_start;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time_start = current_time.tv_sec;
	return (time_start);
}

int	check_death(t_thread_t *data, int s)
{
	pthread_mutex_lock(&data->arg->dead);
	if (s)
		data->arg->finish = 1;
	if (data->arg->finish)
		return (1);
	pthread_mutex_unlock(&data->arg->dead);
	return (0);
}

void	*r_death(void *data)
{
	t_thread_t	*p;

	p = (t_thread_t *)data;
	pthread_mutex_lock(&p->arg->dead);
	if (!check_death(p, 0) && p->arg->finish && get_time - p->ms_eat >= p->arg->t_to_die)
	{
		pthread_mutex_unlock(&p->arg->dead);
		check_death(p, 1);
	}
	pthread_mutex_unlock(&p->arg->dead);
	return (0);
}
void	*routine(void *data)
{
	t_thread_t		*p;
	int				i;
	pthread_t		death;

	i	=	0;
	p = (t_thread_t*)data;
	if (p->id % 2 != 0)
	{
		usleep(p->arg->t_to_die); /* times to die */
	}
	while (!check_death(p, 0))
	{
		pthread_create(&death, NULL, &r_death, p);
		pthread_mutex_lock(&p->l_mutex);
		p->arg->n_time_eat++;
		pthread_mutex_lock(&p->r_mutex);
		pthread_mutex_lock(&p->arg->get_time_eat);
		p->ms_eat = get_time();
		pthread_mutex_unlock(&p->arg->get_time_eat);
		printf("time : %ld\n", p->ms_eat);
		printf("%ld Philo %d has taken fork\n", get_time(), p->id);
		usleep(5000);
		pthread_mutex_unlock(&p->r_mutex);
		pthread_mutex_unlock(&p->l_mutex);
		usleep(p->arg->t_to_sleep);
		pthread_detach(p->pthread_death_id);
	}
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
