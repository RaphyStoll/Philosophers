/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:38:45 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_anim.h"

static void	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->mutex->death_mutex);
	data->simulation_end = true;
	pthread_mutex_unlock(&data->mutex->death_mutex);
}

static bool	check_death(t_philo *philo)
{
	long long	time_since_meal;
	long long	current_time;

	current_time = get_time();
	time_since_meal = current_time - philo->last_meal;
	if (time_since_meal >= philo->data->time_to_die)
	{
		print_status_animated(philo, "died");
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
	while (i < data->nb_philo)
	{
		if (current->meals_eaten >= data->must_eat_count)
			fed_count++;
		current = current->next;
		i++;
	}
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
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(current) || all_philosophers_fed(data))
				return (NULL);
			current = current->next;
			i++;
		}
		update_animation(data);
		usleep(1000);
	}
	return (NULL);
}