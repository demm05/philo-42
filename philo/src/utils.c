#include "../inc/philo.h"
#include <pthread.h>
#include <sys/time.h>

void	cleanup(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
		pthread_mutex_destroy(&info->philos[i++].lock);
	pthread_mutex_destroy(&info->lock);
	free(info->philos);
}

long	elap_time(t_info *info)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - info->time);
}
