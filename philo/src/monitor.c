#include "../inc/philo.h"

static inline bool	is_phil_dead(size_t last_meal, t_info *info)
{
	long	time;

	return (0);
	time = get_current_time() - last_meal;
	if (time < 0)
		return (0);
	return (time >= (unsigned int)(info->die - info->eat));
}

static inline bool	is_simulation_running(t_table *table)
{
	return (mutex_get_bool(&table->info.simulation, &table->simulation));
}

static inline	void	set_neighbours(int id, int *left, int *right, int count)
{
	if (id % 2 == 0)
	{
		*left = (id + 1) % count;
		*right = id;
	}
	else
	{
		*left = id;
		*right = (id + 1) % count;
	}
}

static inline int	phil_check(t_table *table, t_philo *phil)
{
	int		meals;
	int		left_meals;
	int		right_meals;
	size_t	last_meal;
	t_philo	*left;
	t_philo	*right;

	if (phil->id % 2 == 0)
	{
		left = &table->philos[(phil->id + 1) % table->info.philosophers];
		right = &table->philos[phil->id];
	}
	else
	{
		left = &table->philos[phil->id];
		right = &table->philos[(phil->id + 1) % table->info.philosophers];
	}
	pthread_mutex_lock(&phil->mutexes.meal);
	meals = phil->meals_eaten;
	last_meal = phil->times.last_meal;
	pthread_mutex_unlock(&phil->mutexes.meal);
	left_meals = mutex_get_int(&left->meals_eaten, &left->mutexes.meal);
	right_meals = mutex_get_int(&right->meals_eaten, &right->mutexes.meal);
	if (!mutex_get_bool(&left->is_eating, &left->mutexes.meal) && \
		!mutex_get_bool(&right->is_eating, &right->mutexes.meal) && \
		(meals < left_meals || meals < right_meals))
		mutex_set_bool(&phil->can_eat, 1, &phil->mutexes.meal);
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
	while (!mutex_get_bool(&table->init.is_ready, table->init.lock))
		usleep(500);
	while (is_simulation_running(table))
	{
		i = 0;
		while (is_simulation_running(table) && i < table->info.philosophers)
		{
			temp = phil_check(table, &table->philos[i]);
			if (i++ == 0)
				meals = temp;
			else if (temp < meals)
				meals = temp;
		}
		if (meals >= table->info.meals)
			mutex_set_bool(&table->info.simulation, 0, &table->simulation);
	}
	return (NULL);
}
