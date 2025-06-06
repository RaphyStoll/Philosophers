/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:03:59 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/06 09:19:28 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutexes(t_data *data)
{
	data->mutex = malloc(sizeof(t_mutexes));
	if (!data->mutex)
		return (free_data(data), error_msg("Error: malloc mutexes failed"));
	data->mutex->print_lock_initialized = false;
	data->mutex->death_mutex_initialized = false;
	data->mutex->fed_mutex_initialized = false;
	data->mutex->data_mutex_initialized = false;
	data->mutex->meal_mutex_initialized = false;
	if (pthread_mutex_init(&data->mutex->print_lock, NULL) != 0)
		return (free_data(data), error_msg("Error: print_lock init failed"));
	data->mutex->print_lock_initialized = true;
	if (pthread_mutex_init(&data->mutex->death_mutex, NULL) != 0)
		return (free_data(data), error_msg("Error: death_mutex init failed"));
	data->mutex->death_mutex_initialized = true;
	if (pthread_mutex_init(&data->mutex->fed_mutex, NULL) != 0)
		return (free_data(data), error_msg("Error: fed_mutex init failed"));
	data->mutex->fed_mutex_initialized = true;
	if (pthread_mutex_init(&data->mutex->data_mutex, NULL) != 0)
		return (free_data(data), error_msg("Error: data_mutex init failed"));
	if (pthread_mutex_init(&data->mutex->meal_mutex, NULL) != 0)
		return (free_data(data), error_msg("Error: meal_mutex init failed"));
	data->mutex->data_mutex_initialized = true;
	return (true);
}

static bool	init_flags(t_data *data)
{
	data->flags = malloc(sizeof(t_flags));
	if (!data->flags)
		return (free_data(data), error_msg("Error: malloc flags failed"));
	*data->flags = (t_flags){false, false, false, false, false, false};
	return (true);
}

t_data	*init_default_data(t_data *data)
{
	data->nb_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->must_eat_count = -1;
	data->forks = NULL;
	data->philos = NULL;
	data->start_time = get_time();
	data->fed_count = 0;
	data->is_dead = false;
	data->simulation_end = false;
	data->mutex = NULL;
	data->flags = NULL;
	if (!init_mutexes(data) || !init_flags(data))
		return (NULL);
	return (data);
}

static t_philo	*init_philo(t_data *data, int i)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = i + 1;
	new->meals_eaten = 0;
	new->data = data;
	new->last_meal = data->start_time;
	new->left_fork = &data->forks[i];
	new->right_fork = &data->forks[(i + 1) % data->nb_philo];
	new->next = NULL;
	return (new);
}

t_philo	*create_philos(t_data *data)
{
	t_philo	*first;
	t_philo	*prev;
	t_philo	*new;
	int		i;

	first = NULL;
	prev = NULL;
	i = 0;
	while (i < data->nb_philo)
	{
		new = init_philo(data, i);
		if (!new)
			return (NULL);
		if (!first)
			first = new;
		else
			prev->next = new;
		prev = new;
		i++;
	}
	if (prev)
		prev->next = first;
	return (first);
}
