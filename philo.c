#include "philo.h"


t_list	*roll_call(int num, t_dates *dates)
{
	t_philo		*table;
	t_list		*philos;
	int			i;

	i = 0;
	table = malloc(sizeof(t_philo) * num);
	while (i < num)
	{
		table[i].id = i + 1;
		table[i].dates = dates;
		pthread_mutex_init(&table[i].mutex, NULL);
		ft_lstadd_back(&philos, ft_lstnew(&table[i]));
		i++;
	}
	(void)dates;
	ft_lstlast(philos)->next = philos;
	return (philos);
}

void	ft_usleep(int	time)
{
	while (time - 10 >= 0)
	{
		usleep(10);
		time -= 10;
	}
	usleep(time);
}

void	ft_philo_sleep(int	time, int id)
{
	printf("Philo %d is sleeping\n", id);
	ft_usleep(time);
}

void	*birth_philo(void *args)
{
	t_philo *philo_content;
	t_list	*philo_list;
	t_dates	*dates;
	int		count;

	count = 0;
	philo_list = args;
	philo_content = philo_list->content;
	dates = philo_content->dates;
	if (philo_content->id % 2 == 0)
	{
		ft_usleep(100);
		printf("Philo %d is thinking\n", philo_content->id);
	}
	while (dates->die_flag == 0)
	{
		pthread_mutex_lock(&dates->print_mutex);
		pthread_mutex_lock(&philo_content->mutex);
		printf("Philo %d take first spoon\n", philo_content->id);
		pthread_mutex_unlock(&dates->print_mutex);
		pthread_mutex_lock(&((t_philo *)&philo_list->next)->mutex);
		pthread_mutex_lock(&dates->print_mutex);
		printf("Philo %d take second spoon\n", philo_content->id);
		pthread_mutex_unlock(&dates->print_mutex);
		pthread_mutex_lock(&dates->print_mutex);
		printf("Philo %d is eatting\n", philo_content->id);
		count++;
		pthread_mutex_unlock(&dates->print_mutex);
		pthread_mutex_unlock(&philo_content->mutex);
		ft_usleep(dates->time_to_eat);
		pthread_mutex_unlock(&((t_philo *)&philo_list->next)->mutex);
		pthread_mutex_unlock(&dates->print_mutex);
		ft_philo_sleep(dates->time_to_sleep, philo_content->id);
		if (count == dates->eat_number)
			dates->die_flag = 1;
	}
	return (args);
}

void	charge_dates(t_dates *dates, int argc, char **argv)
{
	dates->philo_num = ft_atoi(argv[1]);
	dates->time_to_die = ft_atoi(argv[2]);
	dates->time_to_eat = ft_atoi(argv[3]);
	dates->die_flag = 0;
	dates->time_to_sleep = ft_atoi(argv[4]);
	dates->philos = roll_call(dates->philo_num, dates);
	if (argc == 5)
		dates->eat_number = -1;
	else
	{
		if (ft_atoi(argv[5]) >= 0)
			dates->eat_number = ft_atoi(argv[5]);
		else
			dates->eat_number = 0;
	}
	(void)argc;
}

int	main(int argc, char **argv)
{
	t_dates		dates;
	t_philo		*philo;
	int			i;

	(void)argv;
	if (argc == 5 || argc == 6)
	{
		charge_dates(&dates, argc, argv);
		if (dates.philo_num > 1)
		{
			pthread_mutex_init(&dates.print_mutex, NULL);
			i = 0;
			while (i < dates.philo_num)
			{
				philo = (t_philo *)(dates.philos)->content;
				pthread_create(&philo->philo, NULL, birth_philo, dates.philos);
				dates.philos = dates.philos->next;
				i++;
			}
			while (!dates.die_flag)
			i = 0;
			while (i < dates.philo_num)
			{
				philo = (t_philo *)(dates.philos)->content;
				pthread_join(philo->philo, NULL);
				dates.philos = dates.philos->next;
				i++;
			}
		}
	}
}


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
