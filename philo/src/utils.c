#include "../inc/philo.h"
#include <pthread.h>
#include <unistd.h>

size_t get_current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

size_t	get_print_time(t_info *info)
{
	return (get_current_time() - info->start);
}

void my_sleep(t_info *info, t_philo *phil, unsigned int ms)
{
	size_t	remaining_time;
	size_t	temp;
	size_t	lp;

	pthread_mutex_lock(&phil->time_lock);
	lp = phil->time;
	phil->time += ms;
	pthread_mutex_unlock(&phil->time_lock);
	while (1)
	{
		temp = (get_current_time() - info->start) - lp;
		if (temp > ms)
			remaining_time = 0;
		else
			remaining_time = ms - temp;
		if (remaining_time < 1000)
			break ;
		usleep(500000);
	}
	usleep(remaining_time * 1000);
}

void	cleanup(t_info *info)
{
	int	i;

	if (!info)
		return ;
	if (info->philos)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			pthread_mutex_destroy(&info->philos[i]->time_lock);
			free(info->philos[i++]);
		}
		free(info->philos);
	}
	if (info->init)
	{
		pthread_mutex_destroy(&info->init->lock);
		free(info->init);
	}
	pthread_mutex_destroy(&info->lock);
}

void	wait_for_threads(t_init *init)
{
	pthread_mutex_lock(&init->lock);
	init->initialized++;
	pthread_mutex_unlock(&init->lock);
	while (1)
	{
		pthread_mutex_lock(&init->lock);
		if (init->all_initialized)
		{
			pthread_mutex_unlock(&init->lock);
				return ;
		}
		pthread_mutex_unlock(&init->lock);
		usleep(100);
	}
}
