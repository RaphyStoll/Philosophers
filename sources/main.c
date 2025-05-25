/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:11 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/25 14:04:14 by raphalme         ###   ########.fr       */
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
	if (!start_simulation(data))
		return (free_data(data), 1);
	free_data(data);
	return (0);
}
