#include "../inc/philo.h"
#include <limits.h>

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
			return (printf("Argument doesn't fit in int range\n"));
	}
	if (*ar)
		return (printf("Only digits\n"));
	if (ar != anch && *result == 0)
		return (printf("At least one digit\n"));
	return (0);
}

bool	parse_argv(int argc, char **argv, t_info *info)
{
	if (argc < 5)
	{
		printf("Please provide more arguments\n");
		return (false);
	}
	if (pare_ar(&info->philosophers, argv[1]) || \
		pare_ar(&info->die, argv[2]) || \
		pare_ar(&info->eat, argv[3]) || \
		pare_ar(&info->sleep, argv[4]))
		return (false);
	if (argc == 6)
	{
		if (pare_ar(&info->meals, argv[5]))
			return (false);
	}
	else
		info->meals = -1;
	return (true);
}
