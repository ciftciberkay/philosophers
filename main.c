/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 04:05:50 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/23 20:48:41 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_arg(t_data *datas, char **s, int flag)
{
	datas->nbr_philos = ft_atoi(s[1]);
	datas->time_to_die = ft_atoi(s[2]);
	datas->time_to_eat = ft_atoi(s[3]);
	datas->time_to_sleep = ft_atoi(s[4]);
	if (flag == 1)
	{
		datas->must_eat = ft_atoi(s[5]);
		if (0 >= datas->must_eat)
		{
			printf("Invalid arg!");
			return (0);
		}
	}
	if (0 >= datas->nbr_philos || 0 >= datas->time_to_die
		|| 0 >= datas->time_to_eat || 0 >= datas->time_to_sleep)
	{
		printf("Invalid arg!");
		return (0);
	}
	return (1);
}

int	value_control(char **s)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 1;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			flag = ft_isdigit(s[i][j]);
			j++;
		}
		i++;
	}
	if (flag == 0)
	{
		printf("Not digit arg!");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	datas;
	int		flag;

	flag = 0;
	if (ac > 6 || ac < 5)
	{
		printf("Arg. Error!");
		return (1);
	}
	if (av[5])
		flag = 1;
	if (value_control(av) == 0 || fill_arg(&datas, av, flag) == 0)
		return (1);
}
