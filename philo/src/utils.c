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
	size_t	wake_up;

	wake_up = get_current_time() + ms;
	while (get_current_time() < wake_up)
	{
		if (!is_simulation_running(phil))
			break ;
		usleep(100);
	}
}

bool	cleanup(t_table *table, char *message)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->info.philosophers)
		{
			pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->philos[i++].mutexes.meal);
		}
	}
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->simulation);
	pthread_mutex_destroy(&table->ready);
	if (message)
		printf("%s", message);
	free(table->philos);
	free(table->forks);
	return (0);
}

void	print_action(t_philo *phil, char *s)
{
	long	time;

	time = get_current_time() - phil->times.born_time;
	if (time < 0)
		time = 0;
	if (!mutex_get_bool(&phil->info->simulation, phil->mutexes.simulation))
		return ;
	printf("%ld %d %s\n", time, phil->id + 1, s);
}

bool	is_simulation_running(t_philo *phil)
{
	return (mutex_get_bool(&phil->info->simulation, phil->mutexes.simulation));
}
