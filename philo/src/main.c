#include "../inc/philo.h"
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_info			info;

	if (initialize(argc, argv, &info))
	 return (1);
	printf("%d %d %d %d %d\n", info.num, info.t2d, info.t2e, info.t2s, info.iter);
	//if (create_phil(&info))
	//	return (3);
	cleanup(&info);
	return (0);
}
