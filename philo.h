#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

#define ANSI_COLOR_RED		"\x1b[31m"
#define ANSI_COLOR_GREEN	"\x1b[32m"
#define ANSI_COLOR_YELLOW	"\x1b[33m"
#define ANSI_COLOR_BLUE		"\x1b[34m"
#define ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ANSI_COLOR_CYAN		"\x1b[36m"
#define ANSI_COLOR_RESET	"\x1b[0m"

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
