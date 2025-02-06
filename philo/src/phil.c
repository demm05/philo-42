#include "../inc/philo.h"
#include <pthread.h>
#include <unistd.h>

void	*phil_rot(void *arg)
{
	t_philo	*phil;
	t_info	*info;
	int		i;

	phil = (t_philo *)arg;
	info = phil->info;
	i = 0;
	while (i < 10)
	{
		if (phil->id % 2)
			my_sleep(100, phil);
	}
	return (NULL);
}

int	create_phil(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num)
		pthread_create(&info->philos[i].thread, NULL, phil_rot, &info->philos[i]);
	i = 0;
	while (i < info->num)
		pthread_join(info->philos[i++].thread, NULL);
	return (0);
}
