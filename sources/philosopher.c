/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:59 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/10 06:41:01 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_sim(t_philo *philo)
{
	int running;
	pthread_mutex_lock(&philo->data->mutex->death_mutex);
	running = !philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->mutex->death_mutex);
	if (!running)
	return -42;
	return running;
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int	running;

	philo = (t_philo *)arg;

	while (1)
	{
		if ((running = check_sim(philo)) == -42)
			break;
		philo_eat(philo);
		if ((running = check_sim(philo)) == -42)
			break;
		philo_sleep(philo);
		if ((running = check_sim(philo)) == -42)
			break;
		philo_think(philo);
	}
	return (NULL);
}
