#include "../inc/philo.h"

bool	init_mutexes(t_engine *eng)
{
	size_t	i;

	eng->forks = malloc(sizeof(t_mutex) * eng->philos_count);
	if (!eng->forks)
		return (cleanup(eng, "Malloc error\n"));
	i = 0;
	while (i < eng->philos_count)
	{
		if (pthread_mutex_init(&eng->forks[i], NULL) != 0)
			break ;
		i++;
	}
	if (i != eng->philos_count)
		return (cleanup(eng, "Mutex init error\n"));
	if (pthread_mutex_init(&eng->write_lock, NULL) != 0 || \
		pthread_mutex_init(&eng->meal_lock, NULL) != 0)
		return (cleanup(eng, "Mutex init error\n"));
	return (true);
}

bool	init_philos(t_engine *eng, t_philo *philos, t_mutex *forks)
{
	int		i;
	t_philo	*ph;

	i = -1;
	while (++i < eng->philos_count)
	{
		ph = &philos[i];
		ph->id = i + 1;
		ph->times.die = eng->t2d;
		ph->times.eat = eng->t2e;
		ph->times.sleep = eng->t2s;
		ph->times.born_time = get_current_time();
		ph->times.time = 0;
		ph->times.last_meal = 0;
		ph->meals_to_eat = eng->meals_to_eat;
		ph->meals_eaten = 0;
		ph->mutexes.write_lock = &eng->write_lock;
		ph->mutexes.meal_lock = &eng->meal_lock;
	}
}
