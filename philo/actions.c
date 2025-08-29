/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:00:00 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/29 04:08:07 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	received_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_datas(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_datas(philo, "has taken a fork");
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_datas(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_datas(philo, "has taken a fork");
	}
}

void	ft_eating(t_philo *philo)
{
	received_fork(philo);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal = times_get();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_datas(philo, "is eating");
	ft_sleeping(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_think_sleep(t_philo *philo)
{
	print_datas(philo, "is sleeping");
	ft_sleeping(philo->data->time_to_sleep);
	print_datas(philo, "is thinking");
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;
	int		the_end;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_sleeping(philo->data->time_to_eat / 2);
	pthread_mutex_lock(&philo->data->data_mutex);
	the_end = philo->data->finished;
	pthread_mutex_unlock(&philo->data->data_mutex);
	while (!the_end)
	{
		ft_eating(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		the_end = philo->data->finished;
		pthread_mutex_unlock(&philo->data->data_mutex);
		if (the_end)
			break ;
		ft_think_sleep(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		the_end = philo->data->finished;
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	return (NULL);
}

void	print_datas(t_philo *philo, char *status)
{
	long long	sealtime;
	int			the_end;

	pthread_mutex_lock(&philo->data->data_mutex);
	the_end = philo->data->finished;
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!the_end)
	{
		sealtime = times_get() - philo->data->start_time;
		printf("%lld %d %s\n", sealtime, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
