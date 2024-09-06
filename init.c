
#include "philo.h"

int	ft_create_threads(t_philo **philo)
{
	int	i;

	i = -1;
	(*philo)->t->timer = ft_gettime();
	(*philo)->t->death = 0;
	while (++i < (*philo)->t->nb)
	{
		if (pthread_create(&(*philo)[i].philo_thread, NULL,
			(t_routine)ft_routine, &(*philo)[i]) == -1)
		{
			ft_protect_mutexes(philo);
			ft_clear_philo(philo, -1, i);
			return (1);
		}
		if (pthread_mutex_init(&(*philo)[i].eat_mutex, NULL) == -1)
		{
			ft_protect_mutexes(philo);
			ft_clear_philo(philo, -1, i);
			return (1);
		}
	}
	return (0);
}

t_philo	*ft_init_philo(t_table *t)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(t->nb * sizeof(t_philo));
	while (++i < t->nb && philo)
	{
		philo[i].id = i + 1;
		philo[i].start = 0;
		if (pthread_mutex_init(&philo[i].lfork, NULL) == -1)
		{
			ft_clear_philo(&philo, i, 0);
			write(2, "philo error\n", 13);
			return (NULL);
		}
		if (i != t->nb - 1)
			philo[i].rfork = &philo[i + 1].lfork;
		else
			philo[i].rfork = &philo[0].lfork;
		philo[i].t = t;
	}
	return (philo);
}

int	ft_init_mutex(t_table *t)
{	
	int	etat;

	etat = 1;
	pthread_mutex_init(&t->table_mu, NULL);
	if (pthread_mutex_init(&t->death_mu, NULL))
	{
		ft_destroy_mutex(t, 0);
		etat = 0;
	}
	else if (pthread_mutex_init(&t->meals_mu, NULL))
	{
		ft_destroy_mutex(t, 1);
		etat = 0;
	}
	else if (pthread_mutex_init(&t->print_mu, NULL))
	{
		ft_destroy_mutex(t, 2);
		etat = 0;
	}
	if (!etat)
	{	
		write(2, "mutex problem\n", 15);
		return (0);
	}
	return (1);
}

int	ft_check_int(char *arg)
{	
	long	res;

	if (!ft_onlydigit(arg))
		return (0);
	if (ft_strlen(arg) == 0 || ft_strlen(arg) > INT_SIZE)
		return (0);
	res = ft_atol(arg);
	if (res > MAX || res < 1)
		return (0);
	return ((int)res);
}

int	ft_init_table(t_table *t, char **arg)
{	
	
	t->nb = ft_check_int(arg[1]);
	t->time_d = ft_check_int(arg[2]);
	t->time_e = ft_check_int(arg[3]);
	t->time_s = ft_check_int(arg[4]);
	t->meal = -1;
	t->meals_count = 0;
	if (arg[5])
		t->meal = ft_check_int(arg[5]);
	if (!t->nb || !t->time_d || !t->time_e || !t->time_s || t->meal == 0)
	{
		write(2, "only positiv int, error\n", 25);
		return (0);
	}
	return (1);
}