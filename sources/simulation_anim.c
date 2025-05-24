/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:39:09 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_anim.h"

static bool	create_threads(t_data *data, pthread_t *threads)
{
	t_philo	*current;
	int		i;

	current = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, philosopher_routine, current) != 0)
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

static void	cleanup_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

bool	start_simulation(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor_thread;

	threads = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!threads)
		return (error_msg("Error: malloc threads failed"));
	data->start_time = get_time();
	init_animation(data);
	if (!create_threads(data, threads))
		return (cleanup_animation(), free(threads), false);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (cleanup_animation(), join_threads(data, threads), 
			free(threads), error_msg("Error: monitor thread creation failed"));
	join_threads(data, threads);
	pthread_join(monitor_thread, NULL);
	cleanup_animation();
	cleanup_forks(data);
	free(threads);
	return (true);
}