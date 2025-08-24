/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beciftci <beciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:02:06 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/24 18:02:07 by beciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_arg(t_data *datas, char **s, int flag)
{
	datas->nbr_philos = ft_atoi(s[1]);
	datas->time_to_die = ft_atoll(s[2]);
	datas->time_to_eat = ft_atoll(s[3]);
	datas->time_to_sleep = ft_atoll(s[4]);
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
		printf("Not digit arg!");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	datas;
	int		flag;

	flag = (ac == 6);
	if (ac > 6 || ac < 5)
	{
		printf("Arg. Error!");
		return (1);
	}
	if (value_control(av) == 0 || fill_arg(&datas, av, flag) == 0)
		return (1);
}
