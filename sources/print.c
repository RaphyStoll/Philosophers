/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:04 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/25 16:17:02 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_running(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->mutex->death_mutex);
	result = !data->simulation_end;
	pthread_mutex_unlock(&data->mutex->death_mutex);
	return (result);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->mutex->print_lock);
	if (!philo->data->simulation_end)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->mutex->print_lock);
}
