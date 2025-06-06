/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:20 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/05 08:41:09 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long start, long long end)
{
	return (end - start);
}

void	ft_usleep(long long time)
{
	long long	start;
	long long	elapsed;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= time)
			break;
		// Si on a plus de 1ms à attendre, on peut dormir un peu
		if (time - elapsed > 1)
			usleep(500);  // Dormir 0.5ms
		else
			usleep(1);    // Sinon, micro-sleep minimal
	}
}
