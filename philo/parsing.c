/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slebik <slebik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:53:01 by slebik            #+#    #+#             */
/*   Updated: 2025/03/01 12:53:01 by slebik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) == 0 || check_nb_eat(ac, av) == 0)
			return (0);
		while (i < ac)
		{
			if (string_digits(av[i]) == 0)
				return (0);
			nb = ft_atoi(av[i]);
			if (nb <= 0 && nb > INT_MAX)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	check_nb_eat(int ac, char **av)
{
	if (ac == 6)
	{
		if (ft_atoi(av[5]) == 0)
			return (0);
	}
	return (1);
}

int	string_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '-' )
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}
