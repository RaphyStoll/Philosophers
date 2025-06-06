/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:04 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/06 10:01:35 by raphalme         ###   ########.fr       */
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

static void	ft_putnbr_ll_fd(long long n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putnbr_ll_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	print_status_w(t_philo *philo, const char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->mutex->death_mutex);
	if (!philo->data->simulation_end)
	{
		timestamp = get_time() - philo->data->start_time;
		ft_putnbr_ll_fd(timestamp, 1);
		write(1, " ", 1);
		ft_putnbr_ll_fd(philo->id, 1);
		write(1, " ", 1);
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&philo->data->mutex->death_mutex);
}
