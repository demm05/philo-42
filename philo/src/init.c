#include "../inc/philo.h"
#include <pthread.h>

int	parse_argv(int argc, char **argv, t_info *info)
{
	if (argc < 5)
	{
		printf("Please provide more arguments\n");
		return (2);
	}
	info->num = ft_atoi(argv[1]);
	info->t2d = ft_atoi(argv[2]);
	info->t2e = ft_atoi(argv[3]);
	info->t2s = ft_atoi(argv[4]);
	info->iter = -2;
	if (argc == 6)
		info->iter = ft_atoi(argv[5]);
	if (info->num <= 0 || info->t2d <= 0 || info->t2e <= 0 || \
		info->t2s <= 0 || info->iter == -1)
	{
		printf("Invalid argument\n");
		return (3);
	}
	return (0);
}

int	init_phils(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->num);
	if (!info->philos)
		return (1);
	i = 0;
	while (i < info->num)
	{
		info->philos[i].id = i + 1;
		info->philos[i].meal = 0;
		info->philos[i].info = info;
		if (pthread_mutex_init(&info->philos[i].fork, NULL) != 0)
		{
			printf("Couldn't initialize mutex for %d philosopher\n", i);
			while (i--)
				pthread_mutex_destroy(&info->philos[i].fork);
			free(info->philos);
			return (1);
		}
		i++;
	}
	return (0);
}
