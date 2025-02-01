#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (parse_argv(argc, argv, &info))
		return (1);
	if (init_phils(&info))
		return (2);
	if (create_phil(&info))
		return (3);
	cleanup(&info);
	return (0);
}
