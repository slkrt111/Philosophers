/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slebik <slebik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:46:05 by slebik            #+#    #+#             */
/*   Updated: 2025/03/25 22:46:05 by slebik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct(t_program *program, t_philo **philos,
			pthread_mutex_t **forks, int nb_philo)
{
	*philos = malloc(sizeof(t_philo) * nb_philo);
	*forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!(*philos) || !(*forks))
		return (0);
	init_program(program, *philos);
	return (1);
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nb_philo;

	if (parsing(ac, av) == 0)
		return (printf("\033[31mYou must provide 4 or 5 arguments and positive number (0 is valid \
but not for nb of philo and nb of meal).\033[0m\n"), 0);
	nb_philo = ft_atoi(av[1]);
	if (init_struct(&program, &philos, &forks, nb_philo) == 0)
		return (printf("\033[31mInit failed\033[0m\n"), 0);
	if (nb_philo == 1)
		one_philo(ft_atoi(av[2]));
	else
	{
		init_forks(forks, nb_philo);
		init_philos(philos, &program, forks, av);
		init_threads(&program, forks);
	}
	free(philos);
	free(forks);
	return (1);
}
