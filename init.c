#include "philosopher.h"

int	complete_mutex(int i, t_all_t *data, t_thread_t *thread, pthread_mutex_t *phil)
{
	if (i == 0)
	{
		thread->r_mutex = phil[i + 1];
		thread->l_mutex = phil[i];
	}
	else if (i == data->arg->n_philo - 1)
	{
		thread->r_mutex = phil[0];
		thread->l_mutex = phil[i];
	}
	else if (i > 0 && i < data->arg->n_philo)
	{
		thread->r_mutex = phil[i + 1];
		thread->l_mutex = phil[i];
	}
	else
		return (1);
	return (0);
}

int	send_mutex(t_all_t *data, pthread_mutex_t *phil, pthread_mutex_t *init)
{
	int	i;

	i = 0;
	while (i < data->arg->n_philo)
	{
		complete_mutex(i, data, &data->thread[i], phil);
		i++;
	}
	data->arg->dead = init[0];
	data->arg->get_time_eat = init[1];
	return (0);
}

int	build_mutex(t_all_t *data)
{
	int	i;
	pthread_mutex_t	*m_phil;
	pthread_mutex_t	*m_init;

	i = 0;
	m_phil = malloc(sizeof(pthread_mutex_t) * data->arg->n_philo);
	if (!m_phil)
		return (1);
	m_init = malloc(sizeof(pthread_mutex_t) * 2);
	if (!m_init)
		return (1);
	while (i < data->arg->n_philo)
	{
		pthread_mutex_init(&m_phil[i], NULL); 
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_mutex_init(&m_init[i], NULL);
		i++;
	}
	send_mutex(data, m_phil, m_init);
	return (0);
}

int	init(t_all_t *data, int argc, char **argv)
{
	t_thread_t	*thread;
	int			i;

	i = 0;
	if (argc < 4)
		return (1);
	data->arg = init_arg(argv);
	thread = malloc(sizeof(t_thread_t) * data->arg->n_philo);
	data->thread = thread;
	while (i < data->arg->n_philo)
		thread[i++].arg = data->arg;
	if (build_mutex(data))
		return(1);
	return (0);
}
