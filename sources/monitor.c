/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:42 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/06 08:17:41 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->mutex->death_mutex);
	data->simulation_end = true;
	pthread_mutex_unlock(&data->mutex->death_mutex);
}

static	bool	check_death(t_philo *philo)
{
	long long	time_since_meal;
	long long	current_time;
	long long	last_meal;

	current_time = get_time();
	last_meal = safe_get_last_meal(philo);
	time_since_meal = current_time - last_meal;
	if (time_since_meal >= philo->data->time_to_die)
	{
		if (is_simulation_running(philo->data))
		{
			pthread_mutex_lock(&philo->data->mutex->print_lock);
			printf("%lld %d died\n", current_time - philo->data->start_time,
				philo->id);
			pthread_mutex_unlock(&philo->data->mutex->print_lock);
		}
		end_simulation(philo->data);
		return (true);
	}
	return (false);
}

static bool	all_philosophers_fed(t_data *data)
{
	t_philo	*current;
	int		fed_count;
	int		i;

	if (data->must_eat_count == -1)
		return (false);
	fed_count = 0;
	current = data->philos;
	i = 0;
	pthread_mutex_lock(&data->mutex->data_mutex);
	while (i < data->nb_philo)
	{
		if (current->meals_eaten >= data->must_eat_count)
			fed_count++;
		current = current->next;
		i++;
	}
	pthread_mutex_unlock(&data->mutex->data_mutex);
	if (fed_count == data->nb_philo)
	{
		end_simulation(data);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	t_philo	*current;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->mutex->death_mutex);
		if (data->simulation_end)
		{
			pthread_mutex_unlock(&data->mutex->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->mutex->death_mutex);
		current = data->philos;
		i = -1;
		while (i++, i < data->nb_philo)
		{
			if (check_death(current) || all_philosophers_fed(data))
				return (NULL);
			current = current->next;
		}
		usleep(200);
	}
	return (NULL);
}
