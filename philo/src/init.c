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
		ph->init = &table->init;
		ph->mutexes.write = &table->write;
		ph->mutexes.simulation = &table->simulation;
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
		pthread_mutex_init(&table->init.lock, NULL) != 0
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
	ph->mutexes.left_fork = &forks[left];
	ph->mutexes.right_fork = &forks[right];
}

void	wait_to_initialize(t_init *init)
{
	bool	ready;

	ready = 0;
	pthread_mutex_lock(&init->lock);
	init->initialized++;
	if (init->initialized == init->to_init)
	{
		init->is_ready = 1;
		ready = 1;
	}
	pthread_mutex_unlock(&init->lock);
	while (!ready)
	{
		pthread_mutex_lock(&init->lock);
		if (init->is_ready)
			ready = 1;
		pthread_mutex_unlock(&init->lock);
		usleep(1000);
	}
}
