/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:06:10 by dpavon-g          #+#    #+#             */
/*   Updated: 2022/02/07 17:06:11 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_errors(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (j < (int)ft_strlen(argv[i]))
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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

void	kill_philo(t_dates *dates, t_philo **philo)
{
	pthread_mutex_lock(&dates->die_mutex);
	dates->die_flag = 1;
	my_printf(&dates, philo, "died 💀\n", get_my_time());
	pthread_mutex_unlock(&dates->die_mutex);
	pthread_mutex_unlock(&(*philo)->left_fork);
}
