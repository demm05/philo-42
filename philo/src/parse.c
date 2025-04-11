#include "../inc/philo.h"
#include <limits.h>

static inline int	pare_ar(size_t *result, char *ar)
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

bool	parse_argv(int argc, char **argv, t_engine *eng)
{
	if (argc < 5)
	{
		printf("Please provide more arguments\n");
		return (false);
	}
	if (pare_ar(&eng->philos_count, argv[1]) || \
		pare_ar(&eng->t2d, argv[2]) || \
		pare_ar(&eng->t2e, argv[3]) || \
		pare_ar(&eng->t2s, argv[4]))
		return (false);
	if (argc == 6)
	{
		if (pare_ar(&eng->meals_to_eat, argv[5]))
			return (false);
	}
	else
		eng->meals_to_eat = -1;
	return (true);
}
