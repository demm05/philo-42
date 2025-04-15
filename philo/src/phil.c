#include "../inc/philo.h"

bool	phil_routine(t_philo *phil)
{
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->times.last_meal = get_current_time();
	phil->meals_eaten++;
	phil->is_eating = 1;
	phil->can_eat = 0;
	print_action(phil, FORK);
	print_action(phil, FORK);
	print_action(phil, EAT);
	pthread_mutex_unlock(&phil->mutexes.meal);
	precise_sleep(phil, phil->info->eat);
	mutex_set_bool(&phil->is_eating, 0, &phil->mutexes.meal);
	print_action(phil, SLEEP);
	precise_sleep(phil, phil->info->sleep);
	print_action(phil, THINK);
	return (true);
}

void	*start_philosopher(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	wait_to_initialize(phil->init);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->times.born_time = get_current_time();
	phil->times.last_meal = phil->times.born_time;
	pthread_mutex_unlock(&phil->mutexes.meal);
	while (1)
	{
		while (1)
		{
			if (!mutex_get_bool(&phil->info->simulation, phil->mutexes.simulation))
				return (NULL);
			if (mutex_get_bool(&phil->can_eat, &phil->mutexes.meal))
				break ;
		}
		phil_routine(phil);
	}
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
	pthread_create(&table->monitor, NULL, monitor_table, table);
	i = -1;
	while (++i < table->info.philosophers)
		pthread_join(table->philos[i].thread, NULL);
}
