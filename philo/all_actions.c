/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slebik <slebik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:08:50 by slebik            #+#    #+#             */
/*   Updated: 2025/03/25 23:08:50 by slebik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_philo *philo)
{
	time_t	elapsed_time;

	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	elapsed_time = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!is_he_dead(philo))
		printf("\033[34m%ld %d has taken a fork\033[0m\n",
			elapsed_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	elapsed_time = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!is_he_dead(philo))
		printf("\033[34m%ld %d has taken a fork\033[0m\n",
			elapsed_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	he_eat(t_philo *philo)
{
	time_t	elapsed_time;

	get_fork(philo);
	elapsed_time = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!is_he_dead(philo))
		printf("\033[33m%ld %d is eating\033[0m\n", elapsed_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	usleep(philo->eat_time * 1000);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	philo->eat_time = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	he_think(t_philo *philo)
{
	time_t	elapsed_time;

	elapsed_time = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!is_he_dead(philo))
		printf("\033[32m%ld %d is thinking\033[0m\n", elapsed_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	he_sleep(t_philo *philo)
{
	time_t	elapsed_time;

	elapsed_time = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!is_he_dead(philo))
		printf("\033[37m%ld %d is sleeping\033[0m\n", elapsed_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	usleep(philo->sleep_time * 1000);
}

int	philosopher_dead(t_philo *philo, time_t time_to_die)
{
	time_t	current_time;
	time_t	time_since_last_meal;

	pthread_mutex_lock(philo->meal_lock);
	current_time = get_time_in_ms();
	time_since_last_meal = current_time - philo->last_meal;
	if (time_since_last_meal > time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}
