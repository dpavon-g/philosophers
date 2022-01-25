#include "philo.h"

void	*birth_philo(void *args)
{
	t_dates	*dates;

	dates = (t_dates *)args;

	printf("Philo empieza \n");
	// usleep(1000);
	printf("Philo termina\n");


	return (args);
}

t_list	*roll_call(int num)
{
	t_table		*table;
	t_list		*philos;
	int			i;

	i = 0;
	table = malloc(sizeof(t_table) * num);
	while (i < num)
	{
		table[i].id = i;
		pthread_mutex_init(&table[i].mutex, NULL);
		ft_lstadd_back(&philos, ft_lstnew(&table[i]));
		i++;
	}
	ft_lstlast(philos)->next = philos;
	return (philos);
}

int	main(int argc, char **argv)
{
	t_list		*philos;
	t_dates		dates;
	t_table		*philo;
	int			i;

	philos = NULL;
	if (argc > 1)
	{
		i = 0;
		dates.philo_num = atoi(argv[1]);
		dates.philos = roll_call(dates.philo_num);

		while (i < dates.philo_num)
		{
			philo = (t_table *)(dates.philos)[i];

			i++;
		}
		// while (i < dates.philo_num)
		// {
		// 	
		// }
		// // j = 0;
		// // while (j < dates.philo_num)
		// // {
		// 	pthread_join(dates.philos[0].philo, NULL);
		// 	pthread_join(dates.philos[1].philo, NULL);
		// 	pthread_join(dates.philos[2].philo, NULL);
		// // 	j++;
		// // }
		// pthread_mutex_destroy(&dates.print_mutex);
		// pthread_exit(NULL);
	}
	// (void)table;
}

// void	charge_dates(t_dates *dates, int argc, char **argv)
// {
// 	dates->philo_num = ft_atoi(argv[1]);
// 	dates->time_to_die = ft_atoi(argv[2]);
// 	dates->time_to_eat = ft_atoi(argv[3]);
// 	dates->time_to_sleep = ft_atoi(argv[4]);
// 	if (argc == 5)
// 		dates->eat_number = -1;
// 	else
// 	{
// 		if (ft_atoi(argv[5]) >= 0)
// 			dates->eat_number = ft_atoi(argv[5]);
// 		else
// 			dates->eat_number = 0;
// 	}
// }

// void	leaks(void)
// {
// 	system("leaks philo");
// }

// void	ft_usleep(int time)
// {
// 	int count;

// 	count = 0;
// 	while (count < time)
// 	{
// 		usleep(10);
// 		count += 10;
// 	}
// }

// void	start_dinner(t_dates dates, pthread_mutex_t *philo)
// {
// 	int i;
// 	int eat_count;

// 	i = 1;
// 	eat_count = 1;
// 	while (i <= dates.philo_num)
// 	{
// 		pthread_mutex_init(&philo[i], NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i <= dates.philo_num)
// 	{
// 		if (i % 2 != 0)
// 		{
// 			// printf("Philo %d has taken a fork.\n", i);
// 			// pthread_mutex_lock(&philo[i]);
// 			// printf("Philo %d has taken a fork.\n", i);
// 			// pthread_mutex_lock(&philo[i + 1]);
// 			// printf("Philo %d is eating.\n", i);
// 			// ft_usleep(dates.time_to_eat);
// 			// pthread_mutex_unlock(&philo[i]);
// 			// pthread_mutex_unlock(&philo[i + 1]);
// 		}
// 		i++;
// 	}
// }

// int main(int argc, char **argv)
// {
// 	t_dates		dates;
// 	pthread_mutex_t *philos;

// 	//atexit(leaks);
// 	if (argc == 5 || argc == 6)
// 	{
// 		charge_dates(&dates, argc, argv);
// 		philos = malloc(sizeof(pthread_mutex_t) * dates.philo_num);
// 		start_dinner(dates, philos);
// 		free(philos);
// 	}
// 	else
// 		ft_printf("Error!\n");
// 	return (0);
// 	(void)argv;
// 	(void)argc;
// }
