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

void	state_print(t_philo *phil, char *s)
{
	pthread_mutex_lock(&phil->lock);
	printf("%ld %d %s\n", phil->time, phil->id, s);
	pthread_mutex_unlock(&phil->lock);
}

void	my_sleep(int ms, t_philo *phil)
{
	if (ms < 0)
		return ;
	pthread_mutex_lock(&phil->lock);
	phil->time += ms;	
	pthread_mutex_unlock(&phil->lock);
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
