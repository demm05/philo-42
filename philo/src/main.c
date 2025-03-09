#include "../inc/philo.h"
#include <pthread.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_info			info;
	int				i;

	if (parse_argv(argc, argv, &info))
		return (1);
	if (initialize(&info))
		return (2);
	i = 0;
	while (i < info.num_of_philos)
		pthread_join(info.philos[i++]->thread, NULL);
	cleanup(&info);
	return (0);
}
