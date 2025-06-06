/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:20 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/06 09:17:44 by raphaelferr      ###   ########.fr       */
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
	long long start;
    long long target;

    start = get_time();
    target = start + time;
    
    while (get_time() < target)
    {
        if (target - get_time() > 10)
            usleep(5000);
        else if (target - get_time() > 1)
            usleep(500);
        else
            usleep(10);
    }
}
