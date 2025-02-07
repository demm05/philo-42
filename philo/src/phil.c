#include "../inc/philo.h"
#include <pthread.h>
#include <unistd.h>

int	can_eat(t_philo *phil, t_info *info)
{
	int	left;
		int	right;
	int	c;

	c = 0;
	left = (phil->id - 1 + info->num) % info->num;
	right = (phil->id + 1) % info->num;
	if (left > right)
	{
		left = left + right;
		right = left - right;
		left = left - right;
	}
	pthread_mutex_lock(&info->philos[right].lock);
	pthread_mutex_lock(&info->philos[left].lock);
	pthread_mutex_lock(&phil->lock);
	if (info->philos[left].meals < phil->meals && info->philos[left].state == HUNGRY)
		c = 0;
	else if (info->philos[right].meals < phil->meals && info->philos[right].state == HUNGRY)
		c = 0;
	else if (info->philos[left].state != EATING && info->philos[right].state != EATING)
	{
		c = 1;
		phil->state = EATING;
		phil->meals += 1;
		printf("%ld %d %s\n", phil->time, phil->id + 1, EAT);
	}
	pthread_mutex_unlock(&phil->lock);
	pthread_mutex_unlock(&info->philos[right].lock);
	pthread_mutex_unlock(&info->philos[left].lock);
	return (c);
}

void	update_last_meal(t_philo *phil)
{
	pthread_mutex_lock(&phil->lock);
	phil->last_meal = phil->time;
	pthread_mutex_unlock(&phil->lock);
}

void	set_state(t_philo *phil, enum e_state state)
{
	pthread_mutex_lock(&phil->lock);
	if (state == SLEEPING)
		printf("%ld %d %s\n", phil->time, phil->id + 1, SLEEP);
	phil->state = state;
	pthread_mutex_unlock(&phil->lock);
}

int	is_someone_dead(t_info *info)
{
	int	c;

	c = 0;
	pthread_mutex_lock(&info->lock);
	if (info->dead)
		c = 1;
	pthread_mutex_unlock(&info->lock);
	return (c);
}

int	would_i_die(t_info *info, t_philo *phil)
{
	int	c;

	c = 0;
	pthread_mutex_lock(&info->lock);
	pthread_mutex_lock(&phil->lock);
	if (phil->time + info->t2e - phil->last_meal >= info->t2d)
	{
		c = 1;
		info->dead = 1;
		printf("%ld %d %s\n", phil->time, phil->id + 1, DIE);
	}
	pthread_mutex_unlock(&phil->lock);
	pthread_mutex_unlock(&info->lock);
	return (c);
}

void	*phil_rot(void *arg)
{
	t_philo	*phil;
	t_info	*info;

	phil = (t_philo *)arg;
	info = phil->info;
	while (!would_i_die(info, phil) && !is_someone_dead(info))
	{
		if (can_eat(phil, info))
		{
			my_sleep(info->t2e, phil);
			update_last_meal(phil);
			if (is_someone_dead(info))
				break ;
			set_state(phil, SLEEPING);
			my_sleep(info->t2s, phil);
			if (is_someone_dead(info))
				break ;
			set_state(phil, THINKING);
		}
		else
		{
			pthread_mutex_lock(&phil->lock);
			if (phil->state == THINKING)
				printf("%ld %d %s\n", phil->time, phil->id + 1, THINK);
			phil->state = HUNGRY;
			pthread_mutex_unlock(&phil->lock);
			my_sleep(10, phil);
		}
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
