#include "../inc/philo.h"
#include <limits.h>
#include <pthread.h>

static inline int	pare_ar(int *result, char *ar)
{
	int		sign;
	char	*anch;

	sign = 1;
	anch = ar;
	*result = 0;
	while (*ar == ' ' || (*ar >= 9 && *ar <= 13))
		ar++;
	while (*ar == '-' || *ar == '+')
		if (*ar++ == '-')
			sign *= -1;
	if (sign == -1)
		return (printf("Argument can't be negative\n"));
	while (*ar >= '0' && *ar <= '9' && *ar)
	{
		*result = *result * 10 + (*ar++ - '0');
		if (*result > INT_MAX)
			return (printf("Argument doesnt fit in int range\n"));
	}
	if (*ar)
		return (printf("Only digits\n"));
	if (ar != anch && *result == 0)
		return (printf("At least one digit\n"));
	return (0);
}

static int	parse_argv(int argc, char **argv, t_info *info)
{
	if (argc < 5)
	{
		printf("Please provide more arguments\n");
		return (1);
	}
	if (pare_ar(&info->num, argv[1]) || \
		pare_ar(&info->t2d, argv[2]) || \
		pare_ar(&info->t2e, argv[3]) || \
		pare_ar(&info->t2s, argv[4]))
		return (2);
	if (argc == 6)
	{
		if (pare_ar(&info->iter, argv[5]))
			return (3);
	}
	else
		info->iter = -1;
	return (0);
}

static int	init_mutexs(t_info *info)
{
	int	i;
	
	i = 0;
	if (pthread_mutex_init(&info->lock, NULL))
		return (printf("Couldn't initialize mutex for t_info\n"));
	while (i < info->num)
	{
		info->philos[i].id = i;
		info->philos[i].meals = 0;
		info->philos[i].last_meal = 0;
		info->philos[i].time = 0;
		info->philos[i].info = info;
		info->philos[i].state = THINKING;
		if (pthread_mutex_init(&info->philos[i].lock, NULL))
		{
			printf("Couldn't initialize mutex for %d philosopher\n", i + 1);
			while (i--)
				pthread_mutex_destroy(&info->philos[i].lock);
			free(info->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

int	initialize(int argc, char **argv, t_info *info)
{
	struct timeval	tv;

	if (parse_argv(argc, argv, info))
		return (1);
	info->philos = malloc(sizeof(t_philo) * info->num);
	if (!info->philos)
		return (2);
	if (init_mutexs(info))
		return (3);
	gettimeofday(&tv, NULL);
	info->time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	info->dead = 0;
	return (0);
}
