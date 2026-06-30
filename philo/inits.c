/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beciftci <beciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:01:55 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/29 16:05:43 by beciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_data *data, int ctr)
{
	int	i;

	i = 0;
	while (i < ctr)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	init_fork_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_forks(data, i);
			free(data->forks);
			data->forks = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	if (!init_fork_mutexes(data))
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		destroy_forks(data, data->nbr_philos);
		free(data->forks);
		data->forks = NULL;
		return (0);
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		destroy_forks(data, data->nbr_philos);
		free(data->forks);
		data->forks = NULL;
		return (0);
	}
	return (1);
}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nbr_philos];
		i++;
	}
}

int	all_init(t_data *data)
{
	data->finished = 0;
	data->start_time = times_get();
	data->philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
		return (0);
	if (!init_mutexes(data))
	{
		remove_mutex(data);
		return (0);
	}
	philo_init(data);
	return (1);
}
