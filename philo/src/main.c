#include "../inc/philo.h"
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_info			info;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	info.time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	info.dead = 0;
	if (parse_argv(argc, argv, &info))
		return (1);
	if (init_phils(&info))
		return (2);
	if (create_phil(&info))
		return (3);
	cleanup(&info);
	return (0);
}
