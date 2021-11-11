#include "philo.h"

void	charge_dates(t_dates *dates, int argc, char **argv)
{
	dates->philo_num = ft_atoi(argv[1]);
	dates->time_to_die = ft_atoi(argv[2]);
	dates->time_to_eat = ft_atoi(argv[3]);
	dates->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		dates->eat_number = -1;
	else
	{
		if (ft_atoi(argv[5]) >= 0)
			dates->eat_number = ft_atoi(argv[5]);
		else
			dates->eat_number = 0;
	}
}

void	insert_philos(t_dates dates, t_philos **philos)
{
	int	i;

	i = 0;
	while (i < dates.philo_num)
	{
		//philos->mutex = ();
		i++;
	}
	(void)philos;
	(void)dates;
}

void	create_fork(t_philos **philos, int total)
{
	int i;

	i = 0;
	while (i < total)
	{
		philos[i]->mutex = PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
	(void)i;
}

int main(int argc, char **argv)
{
	t_dates		dates;
	t_philos	*philos;
	
	if (argc == 5 || argc == 6)
	{
		philos = NULL;
		charge_dates(&dates, argc, argv);
		insert_philos(dates, &philos);
		philos = malloc(sizeof(t_philos) * dates.philo_num);
		create_fork(&philos, dates.philo_num);
		free(philos);
	}
	else
		ft_printf("Error!\n");
	return (0);
	(void)philos;
	(void)argv;
	(void)argc;
}
