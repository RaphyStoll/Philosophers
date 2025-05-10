/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:17:15 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/07 16:31:42 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_help_arg(void)
{
	printf("Arguments:\n");
	printf("  number_of_philosophers             "
		"Number of philosophers and forks (≥ 1)\n");
	printf("  time_to_die                        "
		"Time in ms before a philosopher dies if they don't eat\n");
	printf("  time_to_eat                        "
		"Time in ms a philosopher spends eating\n");
	printf("  time_to_sleep                      "
		"Time in ms a philosopher spends sleeping\n");
	printf("  number_of_times_each_philosopher_must_eat  "
		"(optional) Number of meals before the simulation ends\n\n");
}

static void	print_help_flags(void)
{
	printf("Flags:\n");
	printf("  --help,    -h                      "
		"Show this help message and exit\n");
	printf("  --debug,   -d                      "
		"Enable debug output (internal status and checks)\n");
	printf("  --verbose, -v                      "
		"Print all status messages (thinking, sleeping, etc.)\n");
	printf("  --animate, -a                      "
		"Show an ASCII animation of the simulation (if supported)\n");
	printf("  --stats,   -s                      "
		"Print simulation statistics at the end\n");
	printf("  --log,     -l                      "
		"Save a log file of the simulation\n\n");
}

void	print_help(void)
{
	printf("\nUsage: ./philo [number_of_philosophers] [time_to_die] "
		"[time_to_eat] [time_to_sleep] ");
	printf("[number_of_times_each_philosopher_must_eat] [--flags]\n\n");
	print_help_arg();
	print_help_flags();
	printf("Example:\n");
	printf("  ./philo 5 800 200 200 7 --debug --stats\n\n");
}
