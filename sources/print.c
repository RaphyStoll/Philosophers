/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:20:28 by raphaelferr      ###   ########.fr       */
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

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	if (!is_simulation_running(philo->data))
		return ;
# ifdef ANIMATION
	if (philo->data->flags->animate)
	{
		print_status_animated(philo, status);
		return ;
	}
# endif
	pthread_mutex_lock(&philo->data->mutex->print_lock);
	if (is_simulation_running(philo->data))
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->mutex->print_lock);
}