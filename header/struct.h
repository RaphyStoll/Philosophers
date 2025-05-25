/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:56:50 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/25 13:56:52 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include "stdbool.h"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_flags
{
	bool	help;
	bool	debug;
	bool	verbose;
	bool	animate;
	bool	stats;
	bool	log;
}	t_flags;

typedef struct s_mutexes
{
	bool				print_lock_initialized;
	pthread_mutex_t		print_lock;
	bool				death_mutex_initialized;
	pthread_mutex_t		death_mutex;
	bool				fed_mutex_initialized;
	pthread_mutex_t		fed_mutex;
	bool				data_mutex_initialized;
	pthread_mutex_t		data_mutex;
}	t_mutexes;

typedef struct s_data
{
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	*forks;
	long long		start_time;
	t_flags			*flags;
	t_philo			*philos;
	t_mutexes		*mutex;
	bool			is_dead;
	int				fed_count;
	bool			simulation_end;
}	t_data;

#endif