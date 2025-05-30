/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:52 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/29 19:11:37 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print_status_w(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status_w(philo, "is thinking");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	if (!philo->data->simulation_end)
	{
		print_status_w(philo, "has taken a fork");
		print_status_w(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	long long	current_time;

	take_forks(philo);
	pthread_mutex_lock(&philo->data->mutex->death_mutex);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->mutex->death_mutex);
		drop_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex->death_mutex);
	current_time = get_time();
	safe_set_last_meal(philo, current_time);
	safe_increment_meals(philo);
	pthread_mutex_lock(&philo->data->mutex->print_lock);
	if (!philo->data->simulation_end)
		printf("%lld %d is eating\n", current_time - philo->data->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->data->mutex->print_lock);
	ft_usleep(philo->data->time_to_eat);
	drop_forks(philo);
}
