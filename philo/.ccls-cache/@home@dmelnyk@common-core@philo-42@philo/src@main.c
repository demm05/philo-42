#include "../inc/philo.h"
#include <pthread.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if (!parse_argv(argc, argv, &table.info))
		return (1);
	table.info.simulation = 1;
	if (!init_mutexes(&table))
		return (2);
	if (!init_philos(&table, table.forks, table.info.philosophers))
		return (3);
	launch(&table);
	cleanup(&table, NULL);
	return (0);
}
