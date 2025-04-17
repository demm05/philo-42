#include "../inc/philo.h"

static void	think_routine(t_philo *philo, bool silent)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->mutexes.meal);
	time_to_think = (long)(philo->info->die
			- (get_current_time() - philo->times.last_meal)
			- philo->info->eat) / 2;
	pthread_mutex_unlock(&philo->mutexes.meal);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	precise_sleep(philo, time_to_think);
}

static void	eat_routine(t_philo *phil)
{
	pthread_mutex_lock(phil->mutexes.first_fork);
	if (!is_simulation_running(phil))
	{
		pthread_mutex_unlock(phil->mutexes.first_fork);
		return ;
	}
	print_action(phil, FORK);
	pthread_mutex_lock(phil->mutexes.second_fork);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->times.last_meal = get_current_time();
	pthread_mutex_unlock(&phil->mutexes.meal);
	print_action(phil, FORK);
	print_action(phil, EAT);
	precise_sleep(phil, phil->info->eat);
	pthread_mutex_lock(&phil->mutexes.meal);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->mutexes.meal);
	print_action(phil, SLEEP);
	pthread_mutex_unlock(phil->mutexes.second_fork);
	pthread_mutex_unlock(phil->mutexes.first_fork);
	precise_sleep(phil, phil->info->sleep);
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
	if (phil->id % 2)
		think_routine(phil, true);
	while (mutex_get_bool(&phil->info->simulation, phil->mutexes.simulation))
	{
		eat_routine(phil);
		think_routine(phil, false);
	}
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

bool	launch(t_table *table)
{
	int	i;

	if (table->info.philosophers == 1)
	{
		if (pthread_create(&table->philos[0].thread, NULL,
				single_phil, &table->philos[0]) != 0)
			pthread_join(table->philos[0].thread, NULL);
		return (true);
	}
	if (pthread_create(&table->monitor, NULL, monitor_table, table) != 0)
		return (false);
	i = -1;
	while (++i < table->info.philosophers)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				start_philosopher, &table->philos[i]) == 0)
			return (false);
	}
	mutex_set_bool(&table->info.is_ready, 1, &table->ready);
	i = -1;
	while (++i < table->info.philosophers)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->monitor, NULL);
	return (true);
}
