
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_SIZE 10
# define MAX 2147483647

typedef struct timeval	t_timeval;
typedef void			*(*t_routine)(void *);

typedef struct s_table
{
	int					nb;
	int					time_d;
	int					time_e;
	int					time_s;
	int					meal;
	int					meals_count;
	int					death;
	long long			timer;
	pthread_mutex_t		table_mu;
	pthread_mutex_t		meals_mu;
	pthread_mutex_t		death_mu;
	pthread_mutex_t		print_mu;
}					t_table;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	eat_mutex;
	long long		start;
	pthread_t		philo_thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	t_table			*t;
}					t_philo;

int			ft_init_table(t_table *t, char **arg);
int			ft_check_int(char *arg);
int			ft_onlydigit(char *str);
long		ft_atol(const char *str);
int			ft_strlen(char *str);
int			ft_init_mutex(t_table *table);
void		ft_destroy_mutex(t_table *t, int flag);
t_philo		*ft_init_philo(t_table *t);
void		ft_clear_philo(t_philo **philo, int fork, int eat);
int			ft_join_threads(t_philo **philo);
void		ft_sleep(t_philo **philo, long long ms);
long long	ft_gettime(void);
void		ft_clear_table(t_table *table, int flag);
int			ft_create_threads(t_philo **philo);
void		ft_protect_mutexes(t_philo **philo);
int			ft_handle_death(t_table *t, t_philo **philo);
int			ft_check_death(t_philo **philo);
int			ft_check_meals(t_philo **philo);
int			ft_check_eating_time(t_philo **philo, int i, int id);
void		*ft_routine(t_philo *philo);
void		ft_eat(t_philo **philo, int fork);
void		ft_increment_meals(t_philo **philo);
int			ft_take_fork(t_philo **philo);
void		ft_print(t_philo **philo, char *str);
void		ft_philo_sleep(t_philo **philo, int nb);
#endif