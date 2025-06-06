/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:11 by raphalme          #+#    #+#             */
/*   Updated: 2025/06/06 11:27:27 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (error_msg("Error: malloc data failed"), 1);
	if (!init_default_data(data))
		return (1);
	if (!parsing(data, argc, (const char **)argv))
		return (free_data(data), 1);
	if (data->nb_philo == 1)
		return (printf("0 1 has taken a fork\n"),
			printf("%lld 1 died\n", data->time_to_die), free_data(data), 0);
	if (!start_simulation(data))
		return (free_data(data), 1);
	free_data(data);
	return (0);
}
