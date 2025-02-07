#include "../inc/philo.h"
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_info			info;

	if (initialize(argc, argv, &info))
		return (1);
	printf("%d\n", info.t2s);
	if (create_phil(&info))
		return (3);
	cleanup(&info);
	return (0);
}
