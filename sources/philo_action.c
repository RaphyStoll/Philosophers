/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:52 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/25 16:22:18 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void philo_eat(t_philo *philo)
{
    take_forks(philo);
    if (philo->data->simulation_end) {
        drop_forks(philo);
        return;
    }
    
    // Grouper tous les accès en un seul
    long long current_time = get_time();
    pthread_mutex_lock(&philo->data->mutex->data_mutex);
    philo->last_meal = current_time;
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->mutex->data_mutex);
    
    // Print directement
    pthread_mutex_lock(&philo->data->mutex->print_lock);
    if (!philo->data->simulation_end)
        printf("%lld %d is eating\n", current_time - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->mutex->print_lock);
    
    ft_usleep(philo->data->time_to_eat);
    drop_forks(philo);
}

void take_forks(t_philo *philo)
{
	long long timestamp;

	if (philo->id % 2 == 0) {
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	} else {
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->mutex->print_lock);
	if (!philo->data->simulation_end) {
		printf("%lld %d has taken a fork\n", timestamp, philo->id);
		printf("%lld %d has taken a fork\n", timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->data->mutex->print_lock);
}
