/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:28:46 by dpavon-g          #+#    #+#             */
/*   Updated: 2022/02/07 17:08:47 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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

int			check_errors(char **argv, int argc);
useconds_t	get_my_time(void);
void		ft_usleep(useconds_t time);
int			check_time(t_dates **dates, useconds_t *actual, useconds_t past);
void		kill_philo(t_dates *dates, t_philo **philo);
void		my_printf(t_dates **dat, t_philo **ph, char *str, useconds_t time);
t_list		*roll_call(int num, t_dates *dates);
int			t_eat(t_dates **dates, t_philo **philo, useconds_t *action_time);
int			t_sleep(t_dates **dates, t_philo **philo, useconds_t *action_time);
void		*philo_runtine(void *args);
void		charge_dates(t_dates *dates, int argc, char **argv);
void		free_list(t_dates *dates);
void		philo_born(t_dates **dates, t_philo **philo);
void		start_dinner(t_dates *dates, t_philo **philo);
int			main(int argc, char **argv);
long		ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
#endif
