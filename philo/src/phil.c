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
	if (state == EATING)
		printf("%ld %d %s\n", elap_time(info), id + 1, EAT);
	else if (state == THINKING)
		printf("%ld %d %s\n", elap_time(info), id + 1, THINK);
	else if (state == SLEEPING)
		printf("%ld %d %s\n", elap_time(info), id + 1, SLEEP);
	info->philos[id].state = state;
	pthread_mutex_unlock(&info->philos[id].state_lock);
}

int	monitor(t_info *info, t_philo *phil)
{
	int	c;

	c = 1;
	pthread_mutex_lock(&info->lock);
	pthread_mutex_lock(&phil->lock);
	if (info->dead)
		c = 0;
	else if (elap_time(info) - phil->last_meal + info->t2e / 1000 > info->t2d / 1000)
	{
		printf("%ld %d %s\n", elap_time(info) + info->t2e / 1000, phil->id + 1, DIE);
		info->dead = 1;
		c = 0;
	}
	pthread_mutex_unlock(&info->lock);
	pthread_mutex_unlock(&phil->lock);
	return (c);
}

void	*phil_rot(void *arg)
{
	t_philo	*phil;
	t_info	*info;
	int		left;
	int		right;

	phil = (t_philo *)arg;
	info = phil->info;
	phil->last_meal = elap_time(info);
	left = (phil->id - 1 + info->num) % info->num;
	right = (phil->id + 1) % info->num;
	while (monitor(info, phil))
	{
		if (get_state(info, left) != EATING && get_state(info, right) != EATING)
		{
			set_state(info, phil->id, EATING);	
			usleep(info->t2e);
			phil->last_meal = elap_time(info);
			if (!monitor(info, phil))
				break ;
			set_state(info, phil->id, SLEEPING);	
			usleep(info->t2s);
			if (!monitor(info, phil))
				break ;
			set_state(info, phil->id, THINKING);	
		}
		else
		{
			pthread_mutex_lock(&phil->state_lock);
			if (phil->state == THINKING)
				printf("%ld %d %s\n", elap_time(info), phil->id + 1, THINK);
			phil->state = HUNGRY;
			pthread_mutex_unlock(&phil->state_lock);
			usleep(100);
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
