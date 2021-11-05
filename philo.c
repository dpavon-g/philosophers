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

t_philos	*new_philo(pthread_mutex_t mutex)
{
	t_philos	*philo;

	philo = malloc(sizeof(t_list));
	if (!philo)
		return (NULL);
	philo->mutex = mutex;
	philo->next = NULL;
	return (philo);	
}

t_philos	*ft_lstlast2(t_philos *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back2(t_philos **philos, t_philos *new)
{
	t_philos	*temp;

	temp = NULL;
	if (philos)
	{
		temp = *philos;
		if (!temp)
			*philos = new;
		else
		{	
			temp = ft_lstlast2(*philos);
			temp->next = new;
		}
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

int main(int argc, char **argv)
{
	t_dates		dates;
	t_philos	*philos;

	if (argc == 5 || argc == 6)
	{
		philos = NULL;
		charge_dates(&dates, argc, argv);
		insert_philos(dates, &philos);	
	}
	else
		ft_printf("Error!\n");
	return (0);
	(void)philos;
	(void)argv;
	(void)argc;
}
