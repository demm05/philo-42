#include "../inc/philo.h"

inline static void	assign_fork(int count, t_philo *ph, t_mutex *forks);

bool	init_philos(t_table *table, t_mutex *forks, int count)
{
	int		i;
	t_philo	*ph;

	table->philos = malloc(sizeof(t_philo) * table->info.philosophers);
	if (!table->philos)
		return (cleanup(table, "Malloc\n"));
	i = -1;
	while (++i < count)
	{
		ph = &table->philos[i];
		ft_memset(ph, 0, sizeof(t_philo));
		ft_memset(&ph->times, 0, sizeof(t_times));
		ph->id = i;
		ph->info = &table->info;
		ph->mutexes.write = &table->write;
		ph->mutexes.simulation = &table->simulation;
		ph->mutexes.ready_lock = &table->ready;
		if (pthread_mutex_init(&ph->mutexes.meal, NULL) != 0)
			return (false);
		assign_fork(count, ph, forks);
	}
	return (true);
}

bool	init_mutexes(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_mutex) * table->info.philosophers);
	if (!table->forks)
		return (cleanup(table, "Malloc error\n"));
	i = 0;
	while (i < table->info.philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			break ;
		i++;
	}
	if (i != table->info.philosophers)
		return (cleanup(table, "Mutex init error\n"));
	if (pthread_mutex_init(&table->write, NULL) != 0 || \
		pthread_mutex_init(&table->simulation, NULL) != 0 || \
		pthread_mutex_init(&table->ready, NULL) != 0
	)
		return (cleanup(table, "Mutex init error\n"));
	return (true);
}

inline static void	assign_fork(int count, t_philo *ph, t_mutex *forks)
{
	int	left;
	int	right;
	int	id;

	id = ph->id;
	left = id;
	right = id;
	if (id % 2 == 0)
		left = (id + 1) % count;
	else
		right = (id + 1) % count;
	if (DEBUG)
		printf("left:%d\tid: %d\tright: %d\n", left, id, right);
	ph->mutexes.first_fork = &forks[left];
	ph->mutexes.second_fork = &forks[right];
}
