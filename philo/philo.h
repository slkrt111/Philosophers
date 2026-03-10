/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slebik <slebik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:52:40 by slebik            #+#    #+#             */
/*   Updated: 2025/03/01 12:52:40 by slebik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	int				nb_to_eat;
	int				nb_philos;
	int				*dead;
	time_t			last_meal;
	time_t			death_time;
	time_t			eat_time;
	time_t			sleep_time;
	time_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	time_t			start_time;
	t_philo			*philos;
}					t_program;

time_t	get_time_in_ms(void);
int		init_struct(t_program *program, t_philo **philos,
			pthread_mutex_t **forks, int nb_philo);
void	get_fork(t_philo *philo);
void	he_eat(t_philo *philo);
void	he_think(t_philo *philo);
void	he_sleep(t_philo *philo);
int		philosopher_dead(t_philo *philo, time_t time_to_die);
void	init_philos(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char **av);
void	edge_philo(char **av, t_philo *philos, int i, pthread_mutex_t *forks);
void	init_forks(pthread_mutex_t *forks, int nb_philo);
void	init_program(t_program *program, t_philo *philos);
int		parsing(int ac, char **av);
int		string_digits(char *str);
int		ft_atoi(const char *str);
int		is_dead(t_philo *philos);
void	print_dead(t_philo *philo);
int		end_eat(t_philo *philos);
void	one_philo(int death_time);
int		is_he_dead(t_philo *philo);
void	*philosopher_routine(void *ptr);
void	*monitor_it(void *ptr);
void	init_threads(t_program *program, pthread_mutex_t *forks);
void	destroy_mutex(int i, t_program *program, pthread_mutex_t *forks);
int		check_nb_eat(int ac, char **av);

#endif