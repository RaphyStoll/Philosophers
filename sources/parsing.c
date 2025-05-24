/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:52:24 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 16:52:26 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static bool	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (error_msg("Error: malloc forks failed"));
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (error_msg("Error: fork mutex init failed"));
		}
		i++;
	}
	return (true);
}

bool	arg_verif(t_data *data, const int argc, const char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error_msg("Usage: ./philo nb_philo time_to_die time_to_eat"
			"time_to_sleep [must_eat_count]"));
	i = 1;
	while (i < argc)
	{
		if (!is_digit((char *)argv[i]))
			return (error_msg("Error: all arguments must be positive numbers"));
		i++;
	}
	data->nb_philo = ft_atoll(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoll(argv[5]);
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || 
		data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (error_msg("Error: all arguments must be positive"));
	if (data->nb_philo > 200)
		return (error_msg("Error: too many philosophers"));
	return (true);
}

bool	parsing(t_data *data, const int argc, const char **argv)
{
	if (!arg_verif(data, argc, argv))
		return (false);
	if (!init_forks(data))
		return (false);
	data->philos = create_philos(data);
	if (!data->philos)
		return (free_data(data), error_msg("Error: creating philosophers "
			"failed"));
	return (true);
}