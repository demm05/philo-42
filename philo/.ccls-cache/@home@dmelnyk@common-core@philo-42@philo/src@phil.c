#include "../inc/philo.h"

void	phil_routine(t_philo *phil)
{
	if (!is_simulation_running(phil))
		return ;
	pthread_mutex_lock(phil->mutexes.first_fork);
	print_action(phil, FORK);
	if (!is_simulation_running(phil))
	{
		pthread_mutex_unlock(phil->mutexes.first_fork);
		return ;
	}
	pthread_mutex_lock(phil->mutexes.second_fork);
	print_action(phil, FORK);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->times.last_meal = get_current_time();
	pthread_mutex_unlock(&phil->mutexes.meal);
	print_action(phil, EAT);
	precise_sleep(phil, phil->info->eat);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->mutexes.meal);
	pthread_mutex_unlock(phil->mutexes.second_fork);
	pthread_mutex_unlock(phil->mutexes.first_fork);
	print_action(phil, SLEEP);
	precise_sleep(phil, phil->info->sleep);
	print_action(phil, THINK);
	precise_sleep(phil, 2);
}

void	*start_philosopher(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (!mutex_get_bool(&phil->info->is_ready, phil->mutexes.ready_lock))
		usleep(200);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->times.born_time = get_current_time();
	phil->times.last_meal = phil->times.born_time;
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
