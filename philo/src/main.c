#include "../inc/philo.h"
#include <pthread.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_engine	eng;

	ft_memset(&eng, 0, sizeof(t_engine));
	if (!parse_argv(argc, argv, &eng))
		return (1);
	//if (!init_mutexes(&eng))
	//	return (2);
	int	i = 0;
	while (i < eng.philos_count)
	{
		if (i % 2 == 0)
			printf("left: %d\tright: %d\n", (i - 1), );
		else
			printf("left: %d\tright: %d\n", , );
	}
	return (0);
}
