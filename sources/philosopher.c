/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:59 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/05 08:32:33 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	bool	running;

	philo = (t_philo *)arg;
	safe_set_last_meal(philo, get_time());
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex->death_mutex);
		running = !philo->data->simulation_end;
		pthread_mutex_unlock(&philo->data->mutex->death_mutex);
		if (!running)
			break ;
		philo_eat(philo);
		pthread_mutex_lock(&philo->data->mutex->death_mutex);
		running = !philo->data->simulation_end;
		pthread_mutex_unlock(&philo->data->mutex->death_mutex);
		if (!running)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
