/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:52:47 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 16:52:48 by raphaelferr      ###   ########.fr       */
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
# ifdef ANIMATION
	if (data->flags->animate)
		init_animation(data);
# endif
	if (!create_threads(data, threads))
	{
		free(threads);
		return (false);
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		join_threads(data, threads);
		free(threads);
		return (error_msg("Error: monitor thread creation failed"));
	}
	join_threads(data, threads);
	pthread_join(monitor_thread, NULL);
# ifdef ANIMATION
	if (data->flags->animate)
		cleanup_animation();
# endif
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(threads);
	return (true);
}
