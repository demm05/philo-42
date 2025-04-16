#include "../inc/philo.h"

void	phil_routine(t_philo *phil)
{
	if (!is_simulation_running(phil))
		return ;
	pthread_mutex_lock(phil->mutexes.right_fork);
	print_action(phil, FORK);
	if (!is_simulation_running(phil))
	{
		pthread_mutex_unlock(phil->mutexes.right_fork);
		return ;
	}
	pthread_mutex_lock(phil->mutexes.left_fork);
	print_action(phil, FORK);
	print_action(phil, EAT);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->times.last_meal = get_current_time();
	pthread_mutex_unlock(&phil->mutexes.meal);
	precise_sleep(phil, phil->info->eat);
	mutex_set_int(&phil->meals_eaten, phil->meals_eaten + 1, &phil->mutexes.meal);
	pthread_mutex_unlock(phil->mutexes.left_fork);
	pthread_mutex_unlock(phil->mutexes.right_fork);
	print_action(phil, SLEEP);
	precise_sleep(phil, phil->info->sleep);
	print_action(phil, THINK);
	precise_sleep(phil, 1);
}

void	*start_philosopher(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (!mutex_get_bool(&phil->info->is_ready, phil->mutexes.ready_lock))
		usleep(200);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->times.born_time = get_current_time();
	phil->times.last_meal = get_current_time();
	pthread_mutex_unlock(&phil->mutexes.meal);
	while (mutex_get_bool(&phil->info->simulation, phil->mutexes.simulation))
		phil_routine(phil);
	return (NULL);
}

void	*single_phil(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	phil->times.born_time = get_current_time();
	print_action(phil, FORK);
	precise_sleep(phil, phil->info->die);
	print_action(phil, DIE);
	return (NULL);
}

void	launch(t_table *table)
{
	int	i;

	if (table->info.philosophers == 1)
	{
		pthread_create(&table->philos[0].thread, NULL, single_phil, &table->philos[0]);
		pthread_join(table->philos[0].thread, NULL);
		return ;
	}
	pthread_create(&table->monitor, NULL, monitor_table, table);
	i = -1;
	while (++i < table->info.philosophers)
	{
		if (pthread_create(&table->philos[i].thread, NULL, start_philosopher, &table->philos[i]) != 0)
			break ;
	}
	mutex_set_bool(&table->info.is_ready, 1, &table->ready);
	i = -1;
	while (++i < table->info.philosophers)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->monitor, NULL);
}
