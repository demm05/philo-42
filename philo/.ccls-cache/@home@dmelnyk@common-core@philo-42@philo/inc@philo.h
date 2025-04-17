#ifndef PHILO_H
# define PHILO_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define DEBUG 0 

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
	bool	simulation;
	bool	is_ready;
}	t_info;

typedef struct s_times
{
	size_t	last_meal;
	size_t	born_time;
}	t_times;

typedef struct s_mutexes
{
	t_mutex	*first_fork;
	t_mutex	*second_fork;
	t_mutex	*write;
	t_mutex	*simulation;
	t_mutex	*ready_lock;
	t_mutex	meal;
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
	t_mutex		ready;
	t_mutex		write;
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
void	*monitor_table(void *arg);

// Mutex
bool	mutex_get_bool(bool *var, t_mutex *mutex);
void	mutex_set_bool(bool *var, bool value, t_mutex *mutex);
int		mutex_get_int(int *var, t_mutex *mutex);
void	mutex_set_int(int *var, int value, t_mutex *mutex);
bool	is_simulation_running(t_philo *phil);

#endif
