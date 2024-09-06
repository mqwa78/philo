
#include "philo.h"

void	ft_print(t_philo **philo, char *str)
{
	pthread_mutex_lock(&(*philo)->t->print_mu);
	if (!ft_check_meals(philo) && !ft_check_death(philo))
		printf(str, ft_gettime() - (*philo)->t->timer, (*philo)->id);
	pthread_mutex_unlock(&(*philo)->t->print_mu);
}
