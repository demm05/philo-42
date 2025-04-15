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

typedef struct s_init
{
	int		initialized;
	int		to_init;
	bool	is_ready;
	t_mutex	*lock;
}	t_init;

typedef struct s_info
{
	size_t	time;
	int		die;
	int		eat;
	int		sleep;
	int		meals;
	int		philosophers;
	bool	simulation;
}	t_info;

typedef struct s_times
{
	size_t	time;
	size_t	*global_time;
	size_t	last_meal;
	size_t	born_time;
}	t_times;

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write;
	t_mutex	*simulation;
	t_mutex	*time;
	t_mutex	meal;
}	t_mutexes;

typedef struct s_phil
{
	bool		can_eat;
	int			id;
	int			meals_eaten;
	t_init		*init;
	t_info		*info;
	t_times		times;
	t_mutexes	mutexes;
	pthread_t	thread;
}	t_philo;

typedef struct s_table
{
	t_info		info;
	t_init		init;
	pthread_t	monitor;
	t_mutex		lock_time;
	t_mutex		lock_write;
	t_mutex		lock_init;
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
void	wait_to_initialize(t_init *init);

#endif
