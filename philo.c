/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slebik <slebik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:45:22 by slebik            #+#    #+#             */
/*   Updated: 2025/03/29 13:45:22 by slebik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].death_time))
		{
			print_dead(philos);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		pthread_mutex_lock(philos[0].dead_lock);
		if (*philos->dead == 1)
		{
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		pthread_mutex_unlock(philos[0].dead_lock);
		i++;
	}
	return (0);
}

void	print_dead(t_philo *philo)
{
	time_t	elapsed_time;

	elapsed_time = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!is_he_dead(philo))
		printf("\033[31m%ld %d died\033[0m\n", elapsed_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

int	end_eat(t_philo *philos)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	while (i < philos[0].nb_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].nb_to_eat
			&& philos[i].nb_to_eat != -1)
			full_count++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (full_count == philos[0].nb_philos)
	{	
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	one_philo(int death_time)
{
	time_t	start;

	start = get_time_in_ms();
	printf("\033[34m0 0 has taken a fork\033[0m\n");
	usleep(death_time * 1000);
	printf("\033[31m%ld 0 died\033[0m\n", get_time_in_ms() - start);
}

int	is_he_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}
