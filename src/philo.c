/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:30:04 by dpavon-g          #+#    #+#             */
/*   Updated: 2022/02/07 16:52:47 by dpavon-g         ###   ########.fr       */
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
	return (philos);
}

void	*philo_runtine(void *args)
{
	t_philo		*philo_content;
	t_list		*philo_list;
	t_dates		*dates;
	useconds_t	action_time;

	philo_list = args;
	philo_content = philo_list->content;
	dates = philo_content->dates;
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

void	philo_born(t_dates **dates, t_philo **philo)
{
	int			i;
	useconds_t	time;

	i = -1;
	*philo = (t_philo *)((*dates)->philos)->content;
	time = get_my_time();
	while (++i < (*dates)->philo_num)
	{
		*philo = (t_philo *)((*dates)->philos)->content;
		(*philo)->start = time;
		pthread_create(&(*philo)->philo, NULL, philo_runtine, (*dates)->philos);
		(*dates)->philos = (*dates)->philos->next;
	}
	ft_usleep(50);
}

void	start_dinner(t_dates *dates, t_philo **philo)
{
	philo_born(&dates, philo);
	while (1)
	{
		*philo = (t_philo *)(dates->philos)->content;
		if ((int)(get_my_time() - (*philo)->last_eat) > dates->time_to_die)
		{
			if ((*philo)->count != dates->eat_number)
			{
				kill_philo(dates, philo);
				break ;
			}
			else
				break ;
		}
		dates->philos = dates->philos->next;
	}
}

int	main(int argc, char **argv)
{
	t_dates		dates;
	t_philo		*philo;
	int			i;

	if ((argc == 5 || argc == 6) && check_errors(argv, argc))
	{
		charge_dates(&dates, argc, argv);
		pthread_mutex_init(&dates.die_mutex, NULL);
		start_dinner(&dates, &philo);
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
	else
		printf(RED"Error argument\n"RESET);
}
