/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:59 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/05 15:48:23 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	bool	running;

	philo = (t_philo *)arg;
	safe_set_last_meal(philo, get_time());
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
