#include "philosopher.h"

int	build_mutex(t_all_t *data)
{
	int	i;
	pthread_mutex_t	*m_phil;
	pthread_mutex_t	*m_init;

	i = 0;
	m_phil = malloc(sizeof(pthread_mutex_t) * data->arg->n_philo);
	m_init = malloc(sizeof(pthread_mutex_t * 
	while (i < data->arg->n_philo)
	{
		pthread_mutex_init(&m_phil[i], NULL); 
		i++;
	}

}

int	init(t_all_t *data, int argc, char **argv)
{

	if (argc < 4)
		return (1);
	data->arg = init_arg(argv);
	/*build_mutex*/
}
