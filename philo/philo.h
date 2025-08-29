/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:04:33 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/27 17:32:56 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread_id;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	int				finished;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	t_philo			*philos;
}	t_data;

long long	ft_atoll(const char *str);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	times_get(void);
void		ft_sleeping(long long time);
int			all_init(t_data *data);
void		philo_init(t_data *data);
int			loop_start(t_data *data);
void		*routine_philo(void *arg);
void		*routine_screen(void *arg);
void		received_fork(t_philo *philo);
void		ft_eating(t_philo *philo);
void		ft_think_sleep(t_philo *philo);
void		print_datas(t_philo *philo, char *status);
int			die_check(t_data *data);
int			eaten_control(t_data *data);
void		remove_mutex(t_data *data);

#endif