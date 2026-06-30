/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beciftci <beciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:05:04 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/29 16:05:05 by beciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				routine_philo, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	thr_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

int	loop_start(t_data *data)
{
	pthread_t	screen;

	if (pthread_create(&screen, NULL, routine_screen, data) != 0)
		return (0);
	if (!create_threads(data))
		return (0);
	pthread_join(screen, NULL);
	thr_join(data);
	return (1);
}

void	remove_mutex(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nbr_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
}
