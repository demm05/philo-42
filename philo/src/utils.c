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
	size_t	diff;
	size_t	expected_time;
	size_t	global_time;

	pthread_mutex_lock(phil->mutexes.time);
	global_time = phil->info->time;
	pthread_mutex_unlock(phil->mutexes.time);
	expected_time = phil->times.born_time + global_time + ms;
	diff = expected_time - get_current_time();
	while (diff > 5)
	{
		if (diff > 500)
			usleep(500 * 100);
		else
		{
			usleep((diff - 5 ) * 100);
			break ; 
		}
		diff = expected_time - get_current_time();
	}
	while (get_current_time() < expected_time)
		usleep(10);
	phil->times.time += ms;
	pthread_mutex_lock(phil->mutexes.time);
	if (phil->times.time > phil->info->time)
		phil->info->time = phil->times.time;
	pthread_mutex_unlock(phil->mutexes.time);
}

bool	cleanup(t_table *table, char *message)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->info.philosophers)
		{
			pthread_mutex_destroy(&table->forks[i++]);
			pthread_mutex_destroy(&table->philos[i].mutexes.meal);
		}
	}
	pthread_mutex_destroy(&table->lock_write);
	pthread_mutex_destroy(&table->simulation);
	pthread_mutex_destroy(&table->lock_time);
	pthread_mutex_destroy(&table->lock_init);
	if (message)
		printf("%s", message);
	free(table->philos);
	return (0);
}

void	print_action(t_philo *phil, char *s)
{
	long	time;

	if (!mutex_get_bool(&phil->info->simulation, phil->mutexes.simulation))
		return ;
	time = get_current_time() - phil->times.born_time;
	if (time < 0)
		time = 0;
	printf("%ld %d %s\n", time, phil->id + 1, s);
}

bool	mutex_get_bool(bool *var, t_mutex *mutex)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *var;
	pthread_mutex_unlock(mutex);
	return (res);
}

int	mutex_get_int(int *var, t_mutex *mutex)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = *var;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	mutex_set_bool(bool *var, bool value, t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

bool	is_simulation_running(bool *simulation, t_mutex *mutex)
{
	return (mutex_get_bool(simulation, mutex));
}
