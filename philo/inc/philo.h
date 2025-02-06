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
	long			last_meal;
	t_info			*info;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	state_lock;
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

int		ft_atoi(const char *nptr);
int		parse_argv(int argc, char **argv, t_info *info);
int		init_phils(t_info *info);
int		create_phil(t_info *info);
void	cleanup(t_info *info);
long	elap_time(t_info *info);

#endif
