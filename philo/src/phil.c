#include "../inc/philo.h"

bool	is_phil_dead(size_t last_meal, t_info *info)
{
	return (get_current_time() - last_meal <= info->die - info->eat);
}

bool	mutex_get_bool(bool *var, t_mutex *mutex)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *var;
	pthread_mutex_unlock(mutex);
	return (res);
}

bool	phil_routine(t_philo *phil)
{
	while (1)
	{
		if (!mutex_get_bool(&phil->info->simulation, phil->mutexes.simulation))
			return (false);
		if (mutex_get_bool(&phil->can_eat, &phil->mutexes.meal))
			break ;
	}
	pthread_mutex_lock(phil->mutexes.right_fork);
	print_action(phil, FORK);
	pthread_mutex_lock(phil->mutexes.left_fork);
	print_action(phil, FORK);
	pthread_mutex_lock(&phil->mutexes.meal);
	print_action(phil, EAT);
	phil->times.last_meal = get_current_time();
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->mutexes.meal);
	precise_sleep(phil, phil->info->eat);
	pthread_mutex_unlock(phil->mutexes.left_fork);
	pthread_mutex_unlock(phil->mutexes.right_fork);
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
	pthread_mutex_lock(phil->mutexes.write);
	phil->times.born_time = get_current_time();
	pthread_mutex_unlock(phil->mutexes.write);
	while (phil->meals_eaten < phil->info->meals)
		if (!phil_routine(phil))
			break ;
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
