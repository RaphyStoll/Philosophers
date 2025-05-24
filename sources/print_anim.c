/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:38:56 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_anim.h"

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
	if (!is_simulation_running(philo->data))
		return ;
	print_status_animated(philo, status);
}