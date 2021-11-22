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

void	leaks(void)
{
	system("leaks philo");
}

void	ft_usleep(int time)
{
	int count;

	count = 0;
	while (count < time)
	{
		usleep(10);
		count += 10;
	}
}

void	start_dinner(t_dates dates, pthread_mutex_t *philo)
{
	int i;
	int eat_count;

	i = 1;
	eat_count = 1;
	while (i <= dates.philo_num)
	{
		pthread_mutex_init(&philo[i], NULL);
		i++;
	}
	i = 0;
	while (i <= dates.philo_num)
	{
		if (i % 2 != 0)
		{
			printf("Philo %d has taken a fork.\n", i);
			pthread_mutex_lock(&philo[i]);
			printf("Philo %d has taken a fork.\n", i);
			pthread_mutex_lock(&philo[i + 1]);
			printf("Philo %d is eating.\n", i);
			ft_usleep(dates.time_to_eat);
			pthread_mutex_unlock(&philo[i]);
			pthread_mutex_unlock(&philo[i + 1]);
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_dates		dates;
	pthread_mutex_t *philos;
	
	//atexit(leaks);
	if (argc == 5 || argc == 6)
	{
		charge_dates(&dates, argc, argv);
		philos = malloc(sizeof(pthread_mutex_t) * dates.philo_num);
		start_dinner(dates, philos);
		free(philos);
	}
	else
		ft_printf("Error!\n");
	return (0);
	(void)argv;
	(void)argc;
}
