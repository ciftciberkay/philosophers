/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:02:16 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/28 18:33:25 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *str)
{
	int			i;
	long long	b;
	int			o;

	i = 0;
	b = 0;
	o = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			o = -1;
		i++;
	}
	while ((str[i] <= '9' && str[i] >= '0'))
	{
		b = (str[i] - 48) + (b * 10);
		i++;
	}
	if ((b * o) > LLONG_MAX)
		return (0);
	return (b * o);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	b;
	int	o;

	i = 0;
	b = 0;
	o = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			o = -1;
		i++;
	}
	while ((str[i] <= '9' && str[i] >= '0'))
	{
		b = (str[i] - 48) + (b * 10);
		i++;
	}
	return (b * o);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	times_get(void)
{
	struct timeval	time_nbr;

	gettimeofday(&time_nbr, NULL);
	return ((time_nbr.tv_sec * 1000) + (time_nbr.tv_usec / 1000));
}

void	ft_sleeping(long long time)
{
	long long	beginning;

	beginning = times_get();
	while ((times_get() - beginning) < time)
		usleep(500);
}
