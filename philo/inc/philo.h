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
	int				id;
	size_t			time;
	pthread_t		thread;
	pthread_mutex_t	time_lock;
	t_info			*info;
}	t_philo;

typedef struct s_init
{
	bool			all_initialized;
	int				initialized;
	pthread_mutex_t	lock;
}	t_init;


typedef struct s_info
{
	bool			is_threads_inited;
	int				num_of_philos;
	int				t2d;
	int				t2e;
	int				t2s;
	int				ts_to_e;
	size_t			start;
	pthread_mutex_t	lock;
	t_philo			**philos;
	t_init			*init;
}	t_info;

int		parse_argv(int argc, char **argv, t_info *info);
int		initialize(t_info *info);
void	*phil_routine(void *arg);
void	cleanup(t_info *info);
size_t 	get_current_time(void);
size_t	get_print_time(t_info *info);
void	my_sleep(t_info *info, t_philo *phil, unsigned int ms);
void	wait_for_threads(t_init *init);

#endif
