/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:28:46 by dpavon-g          #+#    #+#             */
/*   Updated: 2022/02/04 19:21:49 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

# define RED		"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET	"\x1b[0m"

typedef struct s_dates
{
	long			philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;
	int				die_flag;
	pthread_mutex_t	die_mutex;
	struct s_philo	*table;
	t_list			*philos;
}	t_dates;

typedef struct s_philo
{
	int				id;
	int				count;
	useconds_t		start;
	useconds_t		last_eat;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		philo;
	t_dates			*dates;
}	t_philo;

#endif
