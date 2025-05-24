/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:51:54 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 22:57:39 by raphaelferr      ###   ########.fr       */
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
