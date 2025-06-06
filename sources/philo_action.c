/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:52 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/06 10:09:44 by raphalme         ###   ########.fr       */
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
	int flag;

	flag = 0;
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
	pthread_mutex_lock(&philo->data->mutex->death_mutex);
	if (!philo->data->simulation_end)
	{
		flag = 1;
		pthread_mutex_unlock(&philo->data->mutex->death_mutex);
		print_status_w(philo, "has taken a fork");
		print_status_w(philo, "has taken a fork");
	}
	if (flag == 0)
		pthread_mutex_unlock(&philo->data->mutex->death_mutex);
}

void	philo_eat(t_philo *philo)
{
	long long	c_t;

	c_t = get_time();
	take_forks(philo);
	pthread_mutex_lock(&philo->data->mutex->death_mutex);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->mutex->death_mutex);
		drop_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex->death_mutex);
	c_t = get_time();
	safe_set_last_meal(philo, c_t);
	safe_increment_meals(philo);
	pthread_mutex_lock(&philo->data->mutex->death_mutex);
	if (!philo->data->simulation_end)
	{
		pthread_mutex_lock(&philo->data->mutex->print_lock);
		printf("%lld %d is eating\n", c_t - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->mutex->print_lock);
	}
	pthread_mutex_unlock(&philo->data->mutex->death_mutex);
	ft_usleep(philo->data->time_to_eat);
	drop_forks(philo);
}
