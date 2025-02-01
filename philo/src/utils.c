#include "../inc/philo.h"
#include <pthread.h>

void	cleanup(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
		pthread_mutex_destroy(&info->philos[i++].fork);
	free(info->philos);
}
