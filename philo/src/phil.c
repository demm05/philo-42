#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	pthink(t_info *info, t_philo *phil)
{

}

void	peat(t_info *info, t_philo *phil)
{

}

void	psleep(t_info *info, t_philo *phil)
{

}

void	*phil_routine(void *arg)
{
	t_philo	*phil;
	t_info	*info;
	int		left;
	int		right;

	phil = (t_philo *)arg;
	info = phil->info;
	wait_for_threads(info->init);
	left = phil->id;
	right = (phil->id + 1) % info->num_of_philos;
	return (NULL);
}
