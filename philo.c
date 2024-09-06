
#include "philo.h"

void	ft_increment_meals(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->t->meals_mu);
	(*philo)->t->meals_count++;
	pthread_mutex_unlock(&(*philo)->t->meals_mu);
}

void	ft_philo_sleep(t_philo **philo, int nb)
{
	if (nb == 2)
	{
		ft_print(philo, "%lld %d is sleeping\n");
		ft_sleep(philo, (*philo)->t->time_s);
	}
}

void	ft_eat(t_philo **philo, int fork)
{
	if (fork == 2)
	{
		ft_check_eating_time(philo, 0, 0);
		ft_print(philo, "%lld %d has taken a fork\n");
		ft_print(philo, "%lld %d is eating\n");
		ft_sleep(philo, (*philo)->t->time_e);
		pthread_mutex_unlock(&(*philo)->lfork);
	}
}

int	ft_take_fork(t_philo **philo)
{
	int	f2;

	f2 = 0;
	if (!ft_check_death(philo) && !ft_check_meals(philo))
	{
		pthread_mutex_lock(&(*philo)->lfork);
		f2 += 1;
		if ((*philo)->t->nb != 1)
		{
			pthread_mutex_lock((*philo)->rfork);
			f2 += 1;
		}
		ft_print(philo, "%lld %d has taken a fork\n");
	}
	return (f2);
}

void	*ft_routine(t_philo *philo)
{
	int	i;
	int	f;

	i = 0;
	pthread_mutex_lock(&philo->t->table_mu);
	pthread_mutex_unlock(&philo->t->table_mu);
	if (philo->id % 2 == 0)
		ft_sleep(&philo, 1);
	while (!ft_check_meals(&philo) && philo->t->meal != 0
		&& !ft_check_death(&philo))
	{
		if (philo->t->nb != 1)
			ft_print(&philo, "%lld %d is thinking\n");
		f = ft_take_fork(&philo);
		ft_eat(&philo, f);
		if (f > 0)
			pthread_mutex_unlock((philo)->rfork);
		if (philo->t->meal > 0 && (i + 1) == philo->t->meal && f == 2)
			ft_increment_meals(&philo);
		ft_philo_sleep(&philo, f);
		i++;
		while (!ft_check_death(&philo) && (philo->t->nb == 1 && i))
			usleep(150);
	}
	return (philo);
}
