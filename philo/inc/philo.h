#ifndef PHILO_H
# define PHILO_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
#include <stdbool.h>

typedef struct s_info t_info;

enum	e_state
{
	HUNGRY,
	EATING,
	THINKING,
	SLEEPING
};

typedef struct s_philo
{
	enum e_state	state;
	int				id;
	int				meals;
	long			time;
	t_info			*info;
	pthread_t		thread;
	pthread_mutex_t	lock;
}	t_philo;


typedef struct s_info
{
	int				num;
	int				t2d;
	int				t2e;
	int				t2s;
	int				iter;
	int				dead;
	int				min_meals;
	long			time;
	pthread_mutex_t	lock;
	t_philo			*philos;
}	t_info;

int		initialize(int argc, char **argv, t_info *info);
int		create_phil(t_info *info);

void	cleanup(t_info *info);
long	elap_time(t_info *info);
void	my_sleep(int ms, t_philo *phil);

#endif
