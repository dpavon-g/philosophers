#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <pthread.h>

typedef	struct s_philo
{
	pthread_mutex_t mutex;
	struct s_philo *next;
}	t_philos;

typedef	struct s_dates
{
		int	philo_num;
		int time_to_die;
		int	time_to_eat;
		int	time_to_sleep;
		int	eat_number;
}	t_dates;

#endif
