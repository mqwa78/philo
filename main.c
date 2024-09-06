
#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		write(2, "Invalid arguments\n", 19);
		return (1);
	}
	if (!ft_init_table(&table, av) || !ft_init_mutex(&table))
		return (1);
	philo = ft_init_philo(&table);
	if (!philo || pthread_mutex_lock(&table.table_mu)
		|| ft_create_threads(&philo))
		return (1);
	pthread_mutex_unlock(&table.table_mu);
	if (ft_handle_death(&table, &philo))
	{
		ft_clear_philo(&philo, -1, table.nb);
		ft_clear_table(&table, 1);
		return (1);
	}
	ft_clear_philo(&philo, -1, table.nb);
	ft_clear_table(&table, 0);
	return (0);
}