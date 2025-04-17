#include "../inc/philo.h"

static inline bool	is_phil_dead(size_t last_meal, t_info *info, size_t t)
{
	long	time;

	if (last_meal == 0)
		return (false);
	time = t - last_meal;
	if (time < 0)
		return (false);
	return (time > (unsigned int)info->die);
}

static inline bool	_is_simulation_running(t_table *table)
{
	return (mutex_get_bool(&table->info.simulation, &table->simulation));
}

static inline int	phil_check(t_table *table, t_philo *phil, size_t time)
{
	int		meals;
	size_t	last_meal;

	pthread_mutex_lock(&phil->mutexes.meal);
	meals = phil->meals_eaten;
	last_meal = phil->times.last_meal;
	pthread_mutex_unlock(&phil->mutexes.meal);
	if (is_phil_dead(last_meal, &table->info, time))
	{
		printf("%ld\n", time - last_meal);
		print_action(phil, DIE);
		mutex_set_bool(&table->info.simulation, 0, &table->simulation);
	}
	return (meals);
}

void	*monitor_table(void *arg)
{
	t_table	*table;
	int		i;
	bool	all_ate;
	int		meals;
	size_t	time;

	table = (t_table *)arg;
	while (!mutex_get_bool(&table->info.is_ready, &table->ready))
		usleep(1000);
	while (_is_simulation_running(table))
	{
		i = -1;
		all_ate = 1;
		time = get_current_time();
		while (_is_simulation_running(table) && ++i < table->info.philosophers)
		{
			meals = phil_check(table, &table->philos[i], time);
			if (meals < table->info.meals)
				all_ate = 0;
		}
		if (table->info.meals > 0 && all_ate)
			mutex_set_bool(&table->info.simulation, 0, &table->simulation);
		usleep(1000);
	}
	return (NULL);
}
