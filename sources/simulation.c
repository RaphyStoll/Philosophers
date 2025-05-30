/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:16 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/29 19:09:48 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	create_threads(t_data *data, pthread_t *thread)
{
	t_philo	*current;
	int		i;

	current = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, philosopher_routine, current) != 0)
			return (error_msg("Error: thread creation failed"));
		current = current->next;
		i++;
	}
	return (true);
}

static void	join_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

bool	start_simulation(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor_thread;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!threads)
		return (error_msg("Error: malloc threads failed"));
	data->start_time = get_time();
	data->philos = create_philos(data);
	if (!create_threads(data, threads))
		return (free(threads), false);
	if (!data->philos)
		return (free(threads), false);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (join_threads(data, threads), free(threads),
			!error_msg("Error: monitor thread creation failed"));
	join_threads(data, threads);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (free(threads), true);
}
