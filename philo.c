/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:30:04 by dpavon-g          #+#    #+#             */
/*   Updated: 2022/02/04 19:49:07 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*roll_call(int num, t_dates *dates)
{
	t_list		*philos;
	int			i;

	i = 0;
	philos = NULL;
	dates->table = malloc(sizeof(t_philo) * num);
	while (i < num)
	{
		dates->table[i].id = i + 1;
		dates->table[i].dates = dates;
		pthread_mutex_init(&dates->table[i].left_fork, NULL);
		if (i + 1 < num)
			dates->table[i].right_fork = &dates->table[i + 1].left_fork;
		else
			dates->table[i].right_fork = &dates->table[0].left_fork;
		ft_lstadd_back(&philos, ft_lstnew(&dates->table[i]));
		i++;
	}
	(void)dates;
	if (philos)
		ft_lstlast(philos)->next = philos;
	// free(table);
	return (philos);
}

useconds_t	get_my_time(void)
{
	struct timeval	time_start;

	gettimeofday(&time_start, NULL);
	return (time_start.tv_sec * 1000 + time_start.tv_usec / 1000);
}

void	ft_usleep(useconds_t	time)
{
	useconds_t	start_time;
	useconds_t	my_time;

	start_time = get_my_time();
	my_time = start_time;
	while (my_time - start_time < time)
	{
		usleep(10);
		my_time = get_my_time();
	}
}

void	ft_philo_sleep(int time, int id)
{
	printf("Philo %d is sleeping\n", id);
	ft_usleep(time);
}

int	check_time(t_dates **dates, useconds_t *actual, useconds_t past)
{
	*actual = get_my_time();
	if ((int)(*actual - past) > (*dates)->time_to_die
		|| (*dates)->die_flag == 1)
	{
		(*dates)->die_flag = 1;
		return (1);
	}
	else
		return (0);
}

int	t_eat(t_dates **dates, t_philo **philo, useconds_t *action_time)
{
	pthread_mutex_lock(&(*philo)->left_fork);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	printf("|%d| Philo %d take a fork\n", *action_time - (*philo)->start, (*philo)->id);
	pthread_mutex_lock((*philo)->right_fork);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	printf("|%d| Philo %d take a fork\n", *action_time - (*philo)->start, (*philo)->id);
	pthread_mutex_lock(&(*dates)->die_mutex);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	printf("|%d| Philo %d is eatting\n", *action_time - (*philo)->start, (*philo)->id);
	(*philo)->last_eat = get_my_time();
	pthread_mutex_unlock(&(*dates)->die_mutex);
	ft_usleep((*dates)->time_to_eat);
	(*philo)->count++;
	pthread_mutex_unlock(&(*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
	if ((*philo)->count == (*dates)->eat_number)
		return(1);
	return (0);
}

int	t_sleep(t_dates **dates, t_philo **philo, useconds_t *action_time)
{
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	printf("|%d| Philo %d is sleeping\n", *action_time - (*philo)->start, (*philo)->id);
	ft_usleep((*dates)->time_to_sleep);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	printf("|%d| Philo %d is thinking\n", *action_time - (*philo)->start, (*philo)->id);
	return (0);
}

void	*birth_philo(void *args)
{
	t_philo		*philo_content;
	t_list		*philo_list;
	t_dates		*dates;
	useconds_t	action_time;

	philo_list = args;
	philo_content = philo_list->content;
	dates = philo_content->dates;
	philo_content->start = get_my_time();
	action_time = philo_content->start;
	philo_content->last_eat = philo_content->start;
	if (philo_content->id % 2 == 0)
		ft_usleep(60);
	philo_content->count = 0;
	while (dates->die_flag == 0)
	{
		if (t_eat(&dates, &philo_content, &action_time))
			break ;
		if (t_sleep(&dates, &philo_content, &action_time))
			break ;
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

void	leaks(void)
{
	system("leaks -q philo");
}

void	free_list(t_dates *dates)
{
	int		i;
	t_list	*philo;
	t_list	*aux;

	i = 0;
	philo = dates->philos;
	while (i < dates->philo_num)
	{
		aux = philo->next;
		free(philo);
		philo = aux;
		i++;
	}
	free(dates->table);
}

int	main(int argc, char **argv)
{
	t_dates		dates;
	t_philo		*philo;
	int			i;

	(void)argv;
	atexit(leaks);
	if (argc == 5 || argc == 6)
	{
		charge_dates(&dates, argc, argv);
		pthread_mutex_init(&dates.die_mutex, NULL);
		i = 0;
		while (i < dates.philo_num)
		{
			philo = (t_philo *)(dates.philos)->content;
			pthread_create(&philo->philo, NULL, birth_philo, dates.philos);
			dates.philos = dates.philos->next;
			i++;
		}
		i = 0;
		while (1)
		{
			philo = (t_philo *)(dates.philos)->content;
			if ((int)(get_my_time() - philo->last_eat) > dates.time_to_die)
			{
				if (philo->count != dates.eat_number)
				{
					pthread_mutex_lock(&dates.die_mutex);
					dates.die_flag = 1;
					printf("|%d| Philo %d have die\n", get_my_time() - philo->start, philo->id);
					pthread_mutex_unlock(&dates.die_mutex);
					pthread_mutex_unlock(&philo->left_fork);
					break ;
				}
				else
					break ;
			}
			dates.philos = dates.philos->next;
		}
		i = 0;
		while (i < dates.philo_num)
		{
			philo = (t_philo *)(dates.philos)->content;
			pthread_join(philo->philo, NULL);
			dates.philos = dates.philos->next;
			i++;
		}
		free_list(&dates);
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
