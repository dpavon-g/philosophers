#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <pthread.h>


typedef	struct s_dates
{
	long			philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;
	int				die_flag;
	pthread_mutex_t print_mutex;
	t_list			*philos;
}	t_dates;

typedef	struct s_philo
{
	pthread_mutex_t mutex;
	pthread_t		philo;
	int				id;
	t_dates			*dates;
}	t_philo;

#endif
