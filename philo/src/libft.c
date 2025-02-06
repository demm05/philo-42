#include <limits.h>

int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && *nptr)
	{
		result = result * 10 + (*nptr++ - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (-1);
	}
	return (result * sign);
}

int	is_strnbr(const char *str)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9') && (*str != ' ' || !(*str >= 9 && *str <= 13)))
			return (0);
		str++;
	}
	return (1);
}
