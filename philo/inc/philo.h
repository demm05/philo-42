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

typedef struct s_info
{
	int		die;
	int		eat;
	int		sleep;
	int		meals;
	int		philosophers;
	size_t	time;
	bool	simulation;
}	t_info;

typedef struct s_times
{
	size_t	time;
	size_t	last_meal;
	size_t	born_time;
}	t_times;

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write;
	t_mutex	*meal;
	t_mutex	*simulation;
	t_mutex	*global_time;
}	t_mutexes;

typedef struct s_phil
{
	int			id;
	int			meals_eaten;
	t_info		*info;
	t_times		times;
	t_mutexes	mutexes;
	pthread_t	thread;
}	t_philo;

typedef struct s_table
{
	t_info		info;
	pthread_t	monitor;
	t_mutex		time_lock;
	t_mutex		lock_write;
	t_mutex		lock_meal;
	t_mutex		simulation;
	t_mutex		*forks;
	t_philo		*philos;
}	t_table;

void	precise_sleep(t_philo *phil, unsigned int ms);
bool	cleanup(t_table *eng, char *message);
void	*ft_memset(void *s, int c, size_t n);
size_t	get_current_time(void);
void	print_action(t_philo *phil, char *s);

// Initializatino
bool	parse_argv(int argc, char **argv, t_info *info);
bool	init_mutexes(t_table *table);
bool	init_philos(t_table *eng, t_mutex *forks, int count);
void	launch(t_table *eng);

#endif
