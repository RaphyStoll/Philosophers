/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:28:04 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_simulation_running(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->mutex->death_mutex);
	result = !data->simulation_end;
	pthread_mutex_unlock(&data->mutex->death_mutex);
	return (result);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = philo->data->start_time;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (is_simulation_running(philo->data))
	{
		if (philo->data->nb_philo == 1)
		{
			print_status(philo, "has taken a fork");
			ft_usleep(philo->data->time_to_die);
			break ;
		}
		philo_eat(philo);
		if (!is_simulation_running(philo->data))
			break ;
		philo_sleep(philo);
		if (!is_simulation_running(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
