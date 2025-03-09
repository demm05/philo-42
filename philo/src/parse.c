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
			return (printf("Argument doesnt fit in int range\n"));
	}
	if (*ar)
		return (printf("Only digits\n"));
	if (ar != anch && *result == 0)
		return (printf("At least one digit\n"));
	return (0);
}

int	parse_argv(int argc, char **argv, t_info *info)
{
	if (argc < 5)
	{
		printf("Please provide more arguments\n");
		return (1);
	}
	if (pare_ar(&info->num_of_philos, argv[1]) || \
		pare_ar(&info->t2d, argv[2]) || \
		pare_ar(&info->t2e, argv[3]) || \
		pare_ar(&info->t2s, argv[4]))
		return (2);
	if (argc == 6)
	{
		if (pare_ar(&info->ts_to_e, argv[5]))
			return (3);
	}
	else
		info->ts_to_e= -1;
	return (0);
}
