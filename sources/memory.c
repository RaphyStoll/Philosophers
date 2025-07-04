/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:19 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/29 19:12:29 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->flags)
		free_flags(data->flags);
	if (data->philos)
		free_philo(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->mutex)
		free_mutexes(data->mutex);
	if (data)
		free(data);
}

void	free_flags(t_flags *flags)
{
	if (flags)
		free(flags);
}

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*next;

	if (!philo)
		return ;
	tmp = philo->next;
	while (tmp && tmp != philo)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	if (philo)
		free(philo);
}

void	free_mutexes(t_mutexes *m)
{
	if (!m)
		return ;
	if (m->print_lock_initialized)
	{
		m->print_lock_initialized = false;
		pthread_mutex_destroy(&m->print_lock);
	}
	if (m->death_mutex_initialized)
	{
		m->death_mutex_initialized = false;
		pthread_mutex_destroy(&m->death_mutex);
	}
	if (m->fed_mutex_initialized)
	{
		m->fed_mutex_initialized = false;
		pthread_mutex_destroy(&m->fed_mutex);
	}
	free_mutex2(m);
}

void	free_mutex2(t_mutexes *m)
{
	if (m->data_mutex_initialized)
	{
		m->data_mutex_initialized = false;
		pthread_mutex_destroy(&m->data_mutex);
	}
	if (m->meal_mutex_initialized)
	{
		m->data_mutex_initialized = false;
		pthread_mutex_destroy(&m->meal_mutex);
	}
	if (m)
		free(m);
}
