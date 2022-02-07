/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:06:15 by dpavon-g          #+#    #+#             */
/*   Updated: 2022/02/07 17:06:16 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_printf(t_dates **dat, t_philo **ph, char *str, useconds_t time)
{
	useconds_t	print_time;

	print_time = time - (*ph)->start;
	printf(MAGENTA"|%d| "RESET "Philo %d " CYAN"%s"RESET, print_time,
		(*ph)->id, str);
	(void)*dat;
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

int	t_sleep(t_dates **dates, t_philo **philo, useconds_t *action_time)
{
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	my_printf(dates, philo, "is sleeping 🛌\n", *action_time);
	ft_usleep((*dates)->time_to_sleep);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	my_printf(dates, philo, "in thinking 💬\n", *action_time);
	return (0);
}

int	t_eat(t_dates **dates, t_philo **philo, useconds_t *action_time)
{
	if ((*philo)->count == (*dates)->eat_number)
		return (1);
	pthread_mutex_lock(&(*philo)->left_fork);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	my_printf(dates, philo, "has taken a fork 🥄\n", *action_time);
	pthread_mutex_lock((*philo)->right_fork);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	my_printf(dates, philo, "has taken a fork 🥄\n", *action_time);
	pthread_mutex_lock(&(*dates)->die_mutex);
	if (check_time(dates, action_time, (*philo)->last_eat))
		return (1);
	my_printf(dates, philo, "is eating 🍽\n", *action_time);
	(*philo)->last_eat = get_my_time();
	pthread_mutex_unlock(&(*dates)->die_mutex);
	ft_usleep((*dates)->time_to_eat);
	(*philo)->count++;
	pthread_mutex_unlock(&(*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
	return (0);
}
