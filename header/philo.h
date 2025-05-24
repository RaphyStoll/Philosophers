/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 01:24:57 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 23:12:38 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "struct.h"

//! main
int			main(int argc, char **argv);

//! init
t_philo		*create_philos(t_data *data);
t_data		*init_default_data(t_data *data);

//! parsing
bool		parsing(t_data *data, const int argc, const char **argv);
bool		arg_verif(t_data *data, const int argc, const char **argv);

//! memory
void		free_data(t_data *data);
void		free_flags(t_flags *flags);
void		free_philo(t_philo *philo);
void		free_mutexes(t_mutexes *m);

//! utils
bool		error_msg(const char *msg);

//! mini libft
size_t		ft_strlen(const char *str);
bool		is_digit(char *str);
int			ft_strcmp(char *s1, char *s2);
long long	ft_atoll(const char *str);

//! time
long long	get_time(void);
long long	time_diff(long long start, long long end);
void		ft_usleep(long long time);

//! print
void		print_status(t_philo *philo, char *status);
bool		is_simulation_running(t_data *data);

//! philosopher
void		*philosopher_routine(void *arg);

//! action
void		take_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		drop_forks(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);

//! monitor
void		*monitor_routine(void *arg);

//! simulation
bool		start_simulation(t_data *data);

//! safe_sync - nouvelles fonctions de synchronisation
void		safe_set_last_meal(t_philo *philo, long long time);
long long	safe_get_last_meal(t_philo *philo);
void		safe_increment_meals(t_philo *philo);
int			safe_get_meals_eaten(t_philo *philo);

#endif