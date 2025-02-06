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

void	my_sleep(int ms, t_philo *phil)
{
	if (ms < 0)
		return ;
	phil->time += ms;	
	while (ms > 0)
	{
		if (ms > 1000)
		{
			usleep(1000 * 1000);
			ms -= 1000;
		}
		else
		{
			usleep(ms * 1000);
			break ;
		}
	}
}
