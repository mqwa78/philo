
#include "philo.h"

int	ft_join_threads(t_philo **philo)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < (*philo)->t->nb)
		if (pthread_join((*philo)[i].philo_thread, NULL) != 0)
			error++;
	if (i == (*philo)->t->nb)
		return (0);
	return (error);
}

void	ft_clear_philo(t_philo **philo, int fork, int eat)
{
	int	i;

	if (fork == -1)
		fork = (*philo)->t->nb;
	if (ft_join_threads(philo) > 0)
		write(2, "error pthread_join\n", 20);
	i = -1;
	while (++i < eat)
		pthread_mutex_destroy(&(*philo)[i].eat_mutex);
	i = -1;
	while (++i < fork)
		pthread_mutex_destroy(&(*philo)[i].lfork);
	free(*philo);
}

void	ft_destroy_mutex(t_table *t, int flag)
{
	if (flag == 0)
		pthread_mutex_destroy(&t->table_mu);
	else if (flag == 1)
	{
		pthread_mutex_destroy(&t->table_mu);
		pthread_mutex_destroy(&t->death_mu);
	}
	else if (flag == 2)
	{
		pthread_mutex_destroy(&t->table_mu);
		pthread_mutex_destroy(&t->death_mu);
		pthread_mutex_destroy(&t->meals_mu);
	}
}

void	ft_protect_mutexes(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->t->meals_mu);
	(*philo)->t->meals_count = (*philo)->t->nb;
	pthread_mutex_unlock(&(*philo)->t->meals_mu);
	pthread_mutex_unlock(&(*philo)->t->table_mu);
}

void	ft_clear_table(t_table *table, int flag)
{	
	if (flag == 1)
		write(1, "Someone is dead\n", 17);
	pthread_mutex_destroy(&table->table_mu);
	pthread_mutex_destroy(&table->death_mu);
	pthread_mutex_destroy(&table->print_mu);
	pthread_mutex_destroy(&table->meals_mu);
}