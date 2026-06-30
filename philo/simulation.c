/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beciftci <beciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:05:21 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/29 16:05:22 by beciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_data *data, int i, long long current_time)
{
	data->finished = 1;
	pthread_mutex_unlock(&data->data_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d died\n", current_time - data->start_time,
		data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
}

int	die_check(t_data *data)
{
	int			i;
	long long	now_time;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		now_time = times_get();
		if ((now_time - data->philos[i].last_meal) > data->time_to_die)
		{
			print_death(data, i, now_time);
			return (1);
		}
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	return (0);
}

void	set_finished(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	data->finished = 1;
	pthread_mutex_unlock(&data->data_mutex);
}

int	eaten_control(t_data *data)
{
	int	i;
	int	defeated_eat;

	if (data->must_eat <= 0)
		return (0);
	defeated_eat = 1;
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->philos[i].meals_eaten < data->must_eat)
			defeated_eat = 0;
		pthread_mutex_unlock(&data->data_mutex);
		if (!defeated_eat)
			break ;
		i++;
	}
	if (defeated_eat)
	{
		set_finished(data);
		return (1);
	}
	return (0);
}

void	*routine_screen(void *arg)
{
	t_data	*datas;
	int		the_end;

	datas = (t_data *)arg;
	pthread_mutex_lock(&datas->data_mutex);
	the_end = datas->finished;
	pthread_mutex_unlock(&datas->data_mutex);
	while (!the_end)
	{
		if (die_check(datas) || eaten_control(datas))
			break ;
		usleep(1000);
		pthread_mutex_lock(&datas->data_mutex);
		the_end = datas->finished;
		pthread_mutex_unlock(&datas->data_mutex);
	}
	return (NULL);
}
