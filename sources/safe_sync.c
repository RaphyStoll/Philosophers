/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_sync.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:10 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/25 20:16:08 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_set_last_meal(t_philo *philo, long long time)
{
	if (!philo || !philo->data || !philo->data->mutex)
		return ;
	pthread_mutex_lock(&philo->data->mutex->meal_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->data->mutex->meal_mutex);
}

long long	safe_get_last_meal(t_philo *philo)
{
	long long	time;

	if (!philo || !philo->data || !philo->data->mutex)
		return (0);
	pthread_mutex_lock(&philo->data->mutex->meal_mutex);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->data->mutex->meal_mutex);
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
