#include "../inc/philo.h"
#include <limits.h>
#include <pthread.h>

static int	init_mutexs(t_info *info)
{
	int	i;
	
	i = 0;
	pthread_mutex_init(&info->lock, NULL);
	pthread_mutex_init(&info->init->lock, NULL);
	return (0);
}

static int	init_philos(t_info *info)
{
	t_philo	*phil;
	int		i;

	i = 0;
	while (i < info->num_of_philos)
	{
		phil = malloc(sizeof(t_philo));
		if (!phil)
			return (1);
		info->philos[i] = phil;
		phil->info = info;
		phil->id = i;
		phil->time = 0;
		pthread_mutex_init(&phil->time_lock, NULL);
		pthread_create(&info->philos[i]->thread, NULL, phil_routine, info->philos[i]);
		i++;
	}
	return (0);
}

int	initialize(t_info *info)
{
	info->philos = malloc(sizeof(t_philo *) * info->num_of_philos);
	if (!info->philos)
		return (1);
	info->init = malloc(sizeof(t_init));
	if (!info->init)
		return (1);
	info->init->initialized = 0;
	info->init->all_initialized = 0;
	if (init_mutexs(info))
	{
		return (2);
	}
	if (init_philos(info))
	{
		return (2);
	}
	pthread_mutex_lock(&info->init->lock);
	info->start = get_current_time();
	info->init->all_initialized = 1;
	pthread_mutex_unlock(&info->init->lock);
	return (0);
}
