#include "../inc/philo.h"

void	phil_routine(t_philo *phil)
{
	pthread_mutex_lock(phil->mutexes.right_fork);
	print_action(phil, FORK);
	pthread_mutex_lock(phil->mutexes.left_fork);
	print_action(phil, FORK);
	pthread_mutex_lock(phil->mutexes.meal);
	print_action(phil, EAT);
	phil->times.last_meal = get_current_time();
	phil->meals_eaten++;
	pthread_mutex_unlock(phil->mutexes.meal);
	precise_sleep(phil, phil->info->eat);
	pthread_mutex_unlock(phil->mutexes.left_fork);
	pthread_mutex_unlock(phil->mutexes.right_fork);
	print_action(phil, SLEEP);
	precise_sleep(phil, phil->info->sleep);
	print_action(phil, THINK);
}

void	*start_philosopher(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	pthread_mutex_lock(phil->mutexes.write);
	phil->times.born_time = get_current_time();
	pthread_mutex_unlock(phil->mutexes.write);
	while (phil->meals_eaten < 10)
		phil_routine(phil);
	return (NULL);
}

void	launch(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->info.philosophers)
	{
		if (pthread_create(&table->philos[i].thread, NULL, start_philosopher, &table->philos[i]) != 0)
			break ;
	}
	i = -1;
	while (++i < table->info.philosophers)
		pthread_join(table->philos[i].thread, NULL);
}
