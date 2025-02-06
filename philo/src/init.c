#include "../inc/philo.h"
#include <limits.h>
#include <pthread.h>

static inline int	parsa_ar(int *loc, char *ar)
{
	long	result;
	int		sign;
	char	*anch;

	result = 0;
	sign = 1;
	anch = ar;
	while (*ar == ' ' || (*ar >= 9 && *ar <= 13))
		ar++;
	while (*ar == '-' || *ar == '+')
		if (*ar++ == '-')
			sign *= -1;
	if (sign == -1)
		return (printf("Argument can't be negative\n"));
	while (*ar >= '0' && *ar <= '9' && *ar)
	{
		result = result * 10 + (*ar++ - '0');
		if (result > INT_MAX)
			return (printf("Argument doesnt fit in int range\n"));
	}
	if (*ar)
		return (printf("Only digits\n"));
	if (ar != anch && result == 0)
		return (printf("At least one digit\n"));
	*loc = result;
	return (0);
}

int	parse_argv(int argc, char **argv, t_info *info)
{
	if (argc < 5)
	{
		printf("Please provide more arguments\n");
		return (1);
	}
	if (parsa_ar(&info->num, argv[1]) ||
		parsa_ar(&info->t2d, argv[2]) ||
		parsa_ar(&info->t2e, argv[3]) ||
		parsa_ar(&info->t2s, argv[4]))
		return (2);
	if (argc == 6)
	{
		if (parsa_ar(&info->iter, argv[5]))
			return (2);
	}
	else
		info->iter = -1;
	return (0);
}


int	init_phils(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->num);
	if (!info->philos)
		return (1);
	if (pthread_mutex_init(&info->lock, NULL))
	{
		printf("Couldn't initialize mutex for %d philosopher\n", i);
		return (1);
	}
	i = 0;
	while (i < info->num)
	{
		info->philos[i].id = i;
		info->philos[i].meals = 0;
		info->philos[i].state = THINKING;
		info->philos[i].info = info;
		info->philos[i].last_meal = 0;
		if (pthread_mutex_init(&info->philos[i].lock, NULL) || pthread_mutex_init(&info->philos[i].state_lock, NULL))
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
