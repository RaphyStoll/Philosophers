/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_sync.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:10 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/25 14:05:12 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_set_last_meal(t_philo *philo, long long time)
{
	if (!philo || !philo->data || !philo->data->mutex)
		return ;
	pthread_mutex_lock(&philo->data->mutex->data_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->data->mutex->data_mutex);
}

long long	safe_get_last_meal(t_philo *philo)
{
	long long	time;

	if (!philo || !philo->data || !philo->data->mutex)
		return (0);
	pthread_mutex_lock(&philo->data->mutex->data_mutex);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->data->mutex->data_mutex);
	return (time);
}

void	safe_increment_meals(t_philo *philo)
{
	if (!philo || !philo->data || !philo->data->mutex)
		return ;
	pthread_mutex_lock(&philo->data->mutex->data_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->mutex->data_mutex);
}

int	safe_get_meals_eaten(t_philo *philo)
{
	int	meals;

	if (!philo || !philo->data || !philo->data->mutex)
		return (0);
	pthread_mutex_lock(&philo->data->mutex->data_mutex);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->data->mutex->data_mutex);
	return (meals);
}
