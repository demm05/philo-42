int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && *nptr)
	{
		result = result * 10 + (*nptr++ - '0');
		if (result >= 1000)
			return (-1);
	}
	return (result * sign);
}
