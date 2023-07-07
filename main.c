#include "philosopher.h"

void	*routine()
{
	printf("Test from thread\n");

	return (0);
}

int	main(void)
{
	pthread_t	t1;

	pthread_create(&t1, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	return (0);
}
