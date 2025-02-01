#ifndef PHILO_H
# define PHILO_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinkig"
# define DIE "died"

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo ;

typedef struct s_info
{
	int				num;
	int				t2d;
	int				t2e;
	int				t2s;
	int				iter;
	pthread_mutex_t	dead;
	t_philo			*philos;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				meal;
	t_info			*info;
	pthread_mutex_t	fork;
}	t_philo;

int		ft_atoi(const char *nptr);
int		parse_argv(int argc, char **argv, t_info *info);
int		init_phils(t_info *info);
int		create_phil(t_info *info);
void	cleanup(t_info *info);

#endif
