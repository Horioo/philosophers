/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:19 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/05/16 16:49:12 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(char *str)
{
	long	ret;
	int		i;

	ret = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			error_exit("The Numbers can't be Negative");
		i++;
	}
	while (is_digit(str[i]))
	{
		ret = ret * 10 + str[i++] - '0';
		if (ret > INT_MAX)
		{
			error_exit("Value bigger than INT_MAX\n");
			return (-1);
		}
	}
	return (ret);
}

int	check_sign_chars(char **av)
{
	int	i;
	int	j;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			if (av[j][i] == '+' && i == 0)
				;
			else if (av[j][i] == '-')
				return (1);
			else if (!is_digit(av[j][i]) && av[j][i])
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	parsing(t_table *table, char **av)
{
	if (check_sign_chars(av))
	{
		printf(R "Error on Sign or Chars\n");
		return (1);
	}
	table->philo_nbr = ft_atol(av[1]);
	if (table->philo_nbr > 200 || table->philo_nbr == -1)
	{
		printf(R "Max Philos Reached\n"RST);
		return (1);
	}
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat 
		< 60000 || table->time_to_sleep < 60000)
	{
		error_exit("Error on Timers\n");
		return (1);
	}
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	return (0);
}
