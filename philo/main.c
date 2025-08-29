/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:02:06 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/28 17:56:39 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_single(t_data *data)
{
	if (data->nbr_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_sleeping(data->time_to_die);
		printf("%lld 1 died\n", data->time_to_die);
		return (1);
	}
	return (0);
}

int	validate_args(t_data *data)
{
	if (0 >= data->nbr_philos || 0 >= data->time_to_die
		|| 0 >= data->time_to_eat || 0 >= data->time_to_sleep)
	{
		printf("Invalid Argument Error!\n");
		return (0);
	}
	return (1);
}

int	fill_arg(t_data *data, char **s, int flag)
{
	data->nbr_philos = ft_atoi(s[1]);
	data->time_to_die = ft_atoll(s[2]);
	data->time_to_eat = ft_atoll(s[3]);
	data->time_to_sleep = ft_atoll(s[4]);
	data->must_eat = -1;
	if (flag == 1)
	{
		data->must_eat = ft_atoi(s[5]);
		if (0 >= data->must_eat)
		{
			printf("Invalid Argument Error!\n");
			return (0);
		}
	}
	return (validate_args(data));
}

int	value_control(char **s, int i)
{
	int	j;
	int	flag;

	flag = 1;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			flag = ft_isdigit(s[i][j]);
			if (flag == 0)
				break ;
			j++;
		}
		if (flag == 0)
			break ;
		i++;
	}
	if (flag == 0)
	{
		printf("Argument Value Error\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
	{
		printf("Argument Count Error!\n");
		return (1);
	}
	if (value_control(av, 1) == 0 || fill_arg(&data, av, (ac == 6)) == 0)
		return (1);
	if (philo_single(&data))
		return (0);
	if (!all_init(&data))
	{
		printf("Init Fail!\n");
		return (1);
	}
	if (!loop_start(&data))
	{
		printf("Simulation Error!\n");
		remove_mutex(&data);
		return (1);
	}
	remove_mutex(&data);
	return (0);
}
