/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:19:11 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"
#include <math.h>

extern t_philo_state	*g_philo_states;
extern bool				*g_fork_states;

void	draw_table(t_data *data)
{
	int	i;
	int	center_x;
	int	center_y;

	center_x = 40;
	center_y = 12;
	printf("\033[%d;%dH", center_y - 2, center_x - 10);
	printf(YELLOW "     ╭─────────────────────╮\n");
	printf("\033[%d;%dH", center_y - 1, center_x - 10);
	printf("     │                     │\n");
	printf("\033[%d;%dH", center_y, center_x - 10);
	printf("     │    🍝 SPAGHETTI 🍝   │\n");
	printf("\033[%d;%dH", center_y + 1, center_x - 10);
	printf("     │                     │\n");
	printf("\033[%d;%dH", center_y + 2, center_x - 10);
	printf("     ╰─────────────────────╯" RESET "\n");
	i = 0;
	while (i < data->nb_philo)
	{
		printf("\033[%d;1H", 4 + i);
		printf(CYAN "Philosopher %d: " RESET, i + 1);
		i++;
	}
}

void	draw_philosopher(t_philo *philo, int pos_x, int pos_y)
{
	char	*state_str;
	char	*color;
	char	*emoji;

	if (!g_philo_states)
		return ;
	switch (g_philo_states[philo->id - 1])
	{
		case STATE_THINKING:
			color = BLUE;
			emoji = "🤔";
			state_str = "THINKING";
			break ;
		case STATE_EATING:
			color = GREEN;
			emoji = "🍽️ ";
			state_str = "EATING  ";
			break ;
		case STATE_SLEEPING:
			color = MAGENTA;
			emoji = "😴";
			state_str = "SLEEPING";
			break ;
		case STATE_TAKING_FORK:
			color = YELLOW;
			emoji = "🍴";
			state_str = "FORK    ";
			break ;
		case STATE_DEAD:
			color = RED;
			emoji = "💀";
			state_str = "DEAD    ";
			break ;
		default:
			color = WHITE;
			emoji = "❓";
			state_str = "UNKNOWN ";
			break ;
	}
	printf("%s%s %d%s", color, emoji, philo->id, RESET);
	printf("\033[%d;1H", 4 + philo->id - 1);
	printf(CYAN "Philosopher %d: " RESET "%s%s%s", 
		philo->id, color, state_str, RESET);
	if (philo->meals_eaten > 0)
		printf(" (🍽️ %d)", philo->meals_eaten);
}

void	draw_fork(int fork_id, bool taken, int pos_x, int pos_y)
{
	printf("\033[%d;%dH", pos_y, pos_x);
	if (taken)
		printf(RED "🔴" RESET);
	else
		printf(GREEN "🍴" RESET);
}

void	draw_stats(t_data *data)
{
	long long	current_time;
	long long	elapsed;
	t_philo		*current;
	int			i;

	current_time = get_time();
	elapsed = current_time - data->start_time;
	printf("\033[%d;1H", 20);
	printf(YELLOW "═══════════════════════════════════════════════════════════════\n" RESET);
	printf(LIGHT_CYAN "📊 SIMULATION STATS:\n" RESET);
	printf("⏱️  Elapsed time: %lld ms\n", elapsed);
	printf("👥 Philosophers: %d\n", data->nb_philo);
	printf("⚰️  Time to die: %lld ms\n", data->time_to_die);
	printf("🍽️  Time to eat: %lld ms\n", data->time_to_eat);
	printf("😴 Time to sleep: %lld ms\n", data->time_to_sleep);
	if (data->must_eat_count != -1)
		printf("🎯 Must eat: %d times\n", data->must_eat_count);
	printf("\n" LIGHT_GREEN "📋 ACTIVITY LOG:\n" RESET);
}