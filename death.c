
#include "philo.h"

int	ft_check_eating_time(t_philo **philo, int i, int id)
{
	if (i == 0)
	{
		pthread_mutex_lock(&(*philo)->eat_mutex);
		(*philo)->start = (ft_gettime() - (*philo)->t->timer);
		pthread_mutex_unlock(&(*philo)->eat_mutex);
	}
	if (i == 1)
	{
		pthread_mutex_lock(&(*philo)[id].eat_mutex);
		if ((ft_gettime() - (*philo)->t->timer)
			- (*philo)[id].start >= (*philo)->t->time_d)
		{
			pthread_mutex_unlock(&(*philo)[id].eat_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(*philo)[id].eat_mutex);
	}
	return (0);
}

int	ft_check_meals(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->t->meals_mu);
	if ((*philo)->t->meals_count == (*philo)->t->nb)
	{
		pthread_mutex_unlock(&(*philo)->t->meals_mu);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->t->meals_mu);
	return (0);
}

int	ft_check_death(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->t->death_mu);
	if ((*philo)->t->death == 1)
	{
		pthread_mutex_unlock(&(*philo)->t->death_mu);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->t->death_mu);
	return (0);
}

int	ft_handle_death(t_table *t, t_philo **philo)
{
	int	i;

	while (!ft_check_death(philo) && 
		!ft_check_meals(philo) && t->meal != 0)
	{
		i = 0;
		while (i < t->nb && !ft_check_death(philo) && 
			!ft_check_meals(philo))
		{
			if (ft_check_eating_time(philo, 1, i))
			{
				pthread_mutex_lock(&(*philo)->t->print_mu);
				printf("%lld  %d died\n", ft_gettime()
					- (*philo)->t->timer, (*philo)[i].id);
				pthread_mutex_unlock(&(*philo)->t->print_mu);
				if (pthread_mutex_lock(&t->death_mu))
					return (-1);
				t->death = 1;
				pthread_mutex_unlock(&t->death_mu);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}