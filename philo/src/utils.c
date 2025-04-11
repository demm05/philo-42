#include "../inc/philo.h"
#include <unistd.h>

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*void	precise_sleep(t_philo *phil, unsigned int ms)
{
	size_t	start;
	long	temp;
	size_t	rem;

	pthread_mutex_lock(phil->mutexes.global_time);
	pthread_mutex_lock(phil->mutexes.write);
	start = phil->times.time;
	if (phil->times.time < phil->info->time)
		start = phil->info->time;
	else if (phil->times.time == phil->info->time && \
			!(get_current_time() - phil->times.born_time < phil->times.time + ms))
		phil->info->time = phil->times.time + ms;
	else
	{
	//	printf("\n----NEW GLOBAL TIME\n%d\t%ld\t%ld\n", phil->id, phil->info->time, phil->times.time);
		phil->info->time = phil->times.time;
	}
	phil->times.time += ms;
//	printf("id: %d\tst: %ld\tph: %ld\tgl: %ld\t", phil->id, start, phil->times.time, phil->info->time);
	pthread_mutex_unlock(phil->mutexes.write);
	pthread_mutex_unlock(phil->mutexes.global_time);
	while (1)
	{
		temp = (get_current_time() - phil->times.born_time) - start;
		//printf("\t\t\t%d %ld\n", phil->id, temp);
		if (temp > ms)
			rem = 0;
		else
			rem = ms - temp;
		if (rem < 1000)
			break ;
		usleep(500000);
	}
	if (rem > 0)
		usleep(rem * 1000);
}*/


void	precise_sleep(t_philo *phil, unsigned int ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(5000);
}

bool	cleanup(t_table *table, char *message)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->info.philosophers)
			pthread_mutex_destroy(&table->forks[i++]);
	}
	pthread_mutex_destroy(&table->lock_write);
	pthread_mutex_destroy(&table->lock_meal);
	pthread_mutex_destroy(&table->simulation);
	pthread_mutex_destroy(&table->time_lock);
	if (message)
		printf("%s", message);
	free(table->philos);
	return (0);
}

void	print_action(t_philo *phil, char *s)
{
	bool	t;

	//pthread_mutex_lock(phil->mutexes.simulation);
	//t = phil->info->simulation;
	//pthread_mutex_unlock(phil->mutexes.simulation);
	//if (t)
	//	return ;
	pthread_mutex_lock(phil->mutexes.write);
	printf("%ld %d %s\n", get_current_time() - phil->times.born_time, phil->id, s);
	pthread_mutex_unlock(phil->mutexes.write);
}
