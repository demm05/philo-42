#include "../inc/philo.h"
#include <unistd.h>

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(t_philo *phil, unsigned int ms)
{
	size_t	remaining_time;
	size_t	temp;
	size_t	lp;

	pthread_mutex_lock(phil->mutexes.write_lock);
	lp = phil->times.born_time;
	phil->times.time += ms;
	pthread_mutex_unlock(phil->mutexes.write_lock);
	while (1)
	{
		temp = (get_current_time() - phil->times.born_time) - lp;
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

bool	cleanup(t_engine *eng, char *message)
{
	size_t	i;

	if (eng->forks)
	{
		i = 0;
		while (i < eng->philos_count)
			pthread_mutex_destroy(&eng->forks[i--]);
	}
	pthread_mutex_destroy(&eng->write_lock);
	pthread_mutex_destroy(&eng->meal_lock);
	if (message)
		printf("%s", message);
	return (0);
}

