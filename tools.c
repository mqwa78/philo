
#include "philo.h"

int	ft_strlen(char *str)
{	
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_onlydigit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	int		i;
	long	m;
	long	res;

	res = 0;
	m = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m = -m;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (m * res);
}

void	ft_sleep(t_philo **philo, long long ms)
{
	long long	timestamp;

	timestamp = ft_gettime();
	while (!ft_check_death(philo) && !ft_check_meals(philo)
		&& ft_gettime() - timestamp < ms)
		usleep(150);
}

long long	ft_gettime(void)
{
	t_timeval		now;
	unsigned long	time;

	if (gettimeofday(&now, NULL) != 0)
	{
		write(2, "Error in ft_gettime\n", 21);
		return (-1);
	}
	time = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return (time);
}
