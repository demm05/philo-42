#include "../inc/philo.h"

static inline bool	is_phil_dead(size_t last_meal, t_info *info)
{
	long	time;

	time = get_current_time() - last_meal;
	if (time < 0)
		return (0);
	return (time >= (unsigned int)info->die);
}

static inline bool	_is_simulation_running(t_table *table)
{
	return (mutex_get_bool(&table->info.simulation, &table->simulation));
}

static inline int	phil_check(t_table *table, t_philo *phil)
{
	int		meals;
	size_t	last_meal;

	pthread_mutex_lock(&phil->mutexes.meal);
	meals = phil->meals_eaten;
	last_meal = phil->times.last_meal;
	pthread_mutex_unlock(&phil->mutexes.meal);
	if (is_phil_dead(last_meal, &table->info))
	{
		print_action(phil, DIE);
		mutex_set_bool(&table->info.simulation, 0, &table->simulation);
	}
	return (meals);
}

void	*monitor_table(void *arg)
{
	t_table	*table;
	int		i;
	int		meals;
	int		temp;

	table = (t_table *)arg;
	while (!mutex_get_bool(&table->info.is_ready, &table->ready))
		usleep(1000);
	usleep(1000);
	while (_is_simulation_running(table))
	{
		i = -1;
		while (_is_simulation_running(table) && ++i < table->info.philosophers)
		{
			temp = phil_check(table, &table->philos[i]);
			if (table->info.meals < 0)
				;
			else if (i == 0)
				meals = temp;
			else if (temp < meals)
				meals = temp;
		}
		if (table->info.meals > 0 && meals >= table->info.meals)
			mutex_set_bool(&table->info.simulation, 0, &table->simulation);
		usleep(500);
	}
	return (NULL);
}
