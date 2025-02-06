#include "../inc/philo.h"
#include <pthread.h>
#include <unistd.h>


enum e_state	get_state(t_info *info, int id)
{
	enum e_state	r;

	pthread_mutex_lock(&info->philos[id].state_lock);
	r = info->philos[id].state;
	pthread_mutex_unlock(&info->philos[id].state_lock);
	return (r);
}

void	set_state(t_info *info, int id, enum e_state state)
{
	pthread_mutex_lock(&info->philos[id].state_lock);
	info->philos[id].state = state;
	pthread_mutex_unlock(&info->philos[id].state_lock);
}

int	monitor(t_info *info, t_philo *phil)
{
	int	c;

	c = 1;
	pthread_mutex_lock(&info->lock);
	if (info->dead)
		c = 0;
	else if (elap_time(info) - phil->last_meal > info->t2d / 1000)
	{
		printf("%ld %d %s\n", elap_time(info), phil->id, DIE);
		info->dead = 1;
		c = 0;
	}
	pthread_mutex_unlock(&info->lock);
	return (c);
}

int	can_eat(t_info *info, int id)
{
	int	left;
	int	right;

	left = (id - 2 + info->num) % info->num;
	right = id % info->num ;
	if (get_state(info, left) == EATING || get_state(info, right) == EATING)
		return (0);
	else if (info->philos[id].meals == info->philos[right].meals)
		return (0);
	return (1);
}

void	eat(t_info *info, int id)
{
	int	left;
	int	right;

	left = id - 1;
	right = id % info->num ;
	pthread_mutex_lock(&info->philos[left].lock);
	pthread_mutex_lock(&info->philos[right].lock);
	set_state(info, id, EATING);

	info->philos[id].meals += 1;
	printf("%ld %d %s\n", elap_time(info), id, FORK);
	printf("%ld %d %s\n", elap_time(info), id, EAT);
	usleep(info->t2e);

	set_state(info, id, THINKING);
	pthread_mutex_unlock(&info->philos[left].lock);
	pthread_mutex_unlock(&info->philos[right].lock);
}

void	*phil_rot(void *arg)
{
	t_philo	*phil;
	t_info	*info;
	bool	test;

	phil = (t_philo *)arg;
	info = phil->info;
	phil->last_meal = elap_time(info);
	test = 0;
	while (monitor(info, phil))
	{
		if (!can_eat(info, phil->id))
		{
			if (get_state(info, phil->id) == THINKING)
				printf("%ld %d %s\n", elap_time(info), phil->id, THINK);
			usleep(100);
			set_state(info, phil->id, HUNGRY);
			continue ;
		}
		eat(info, phil->id);
		phil->last_meal = elap_time(info);
		if (!monitor(info, phil))
			break ;
		printf("%ld %d %s\n", elap_time(info), phil->id, SLEEP);
		usleep(info->t2s);
		phil->last_meal = elap_time(info);
		printf("%ld %d %s\n", elap_time(info), phil->id, THINK);
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
