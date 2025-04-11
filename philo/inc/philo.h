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
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_times
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	time;
	size_t	last_meal;
	size_t	born_time;
}	t_times;

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write_lock;
	t_mutex	*meal_lock;
}	t_mutexes;

typedef struct s_phil
{
	int			id;
	int			meals_eaten;
	int			meals_to_eat;
	t_times		times;
	t_mutexes	mutexes;
}	t_philo;

typedef struct s_engine
{
	size_t	t2e;
	size_t	t2s;
	size_t	t2d;
	size_t	philos_count;
	size_t	meals_to_eat;
	t_mutex	write_lock;
	t_mutex	meal_lock;
	t_mutex	*forks;
	t_philo	*philos;
}	t_engine;

void	precise_sleep(t_philo *phil, unsigned int ms);
bool	parse_argv(int argc, char **argv, t_engine *eng);
bool	cleanup(t_engine *eng, char *message);
bool	init_mutexes(t_engine *eng);
void	*ft_memset(void *s, int c, size_t n);
size_t	get_current_time(void);

#endif
