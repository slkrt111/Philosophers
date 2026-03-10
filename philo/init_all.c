/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slebik <slebik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:57:37 by slebik            #+#    #+#             */
/*   Updated: 2025/03/31 16:21:52 by slebik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].death_time = (time_t)ft_atoi(av[2]);
		philos[i].eat_time = (time_t)ft_atoi(av[3]);
		philos[i].sleep_time = (time_t)ft_atoi(av[4]);
		philos[i].nb_philos = (time_t)ft_atoi(av[1]);
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].start_time = program->start_time;
		philos[i].last_meal = get_time_in_ms();
		edge_philo(av, philos, i, forks);
		i++;
	}
}

void	edge_philo(char **av, t_philo *philos, int i, pthread_mutex_t *forks)
{
	if (av[5])
		philos[i].nb_to_eat = ft_atoi(av[5]);
	else
		philos[i].nb_to_eat = -1;
	if (i == 0)
		philos[i].r_fork = &forks[philos[i].nb_philos - 1];
	else
		philos[i].r_fork = &forks[i - 1];
}

void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	program->start_time = get_time_in_ms();
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
