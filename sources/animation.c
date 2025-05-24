/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:19:28 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"
#include <math.h>

static t_philo_state	*g_philo_states = NULL;
static bool				*g_fork_states = NULL;
static pthread_mutex_t	g_animation_mutex = PTHREAD_MUTEX_INITIALIZER;

void	init_animation(t_data *data)
{
	int	i;

	printf(CLEAR_SCREEN CURSOR_HOME HIDE_CURSOR);
	g_philo_states = malloc(sizeof(t_philo_state) * data->nb_philo);
	g_fork_states = malloc(sizeof(bool) * data->nb_philo);
	if (!g_philo_states || !g_fork_states)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		g_philo_states[i] = STATE_THINKING;
		g_fork_states[i] = false;
		i++;
	}
	printf(LIGHT_CYAN "🍝 PHILOSOPHERS SIMULATION 🍝\n" RESET);
	printf(YELLOW "═══════════════════════════════════════════════════════════════\n" RESET);
	draw_table(data);
}

void	cleanup_animation(void)
{
	printf(SHOW_CURSOR);
	if (g_philo_states)
		free(g_philo_states);
	if (g_fork_states)
		free(g_fork_states);
	g_philo_states = NULL;
	g_fork_states = NULL;
}

void	set_philo_state(t_philo *philo, t_philo_state state)
{
	if (!g_philo_states)
		return ;
	pthread_mutex_lock(&g_animation_mutex);
	g_philo_states[philo->id - 1] = state;
	pthread_mutex_unlock(&g_animation_mutex);
}

static void	get_position(int philo_id, int total, int *x, int *y)
{
	double	angle;
	int		radius;
	int		center_x;
	int		center_y;

	radius = 8;
	center_x = 40;
	center_y = 12;
	angle = (2.0 * M_PI * (philo_id - 1)) / total;
	*x = center_x + (int)(radius * cos(angle));
	*y = center_y + (int)(radius * sin(angle));
}

void	update_animation(t_data *data)
{
	t_philo	*current;
	int		x;
	int		y;
	int		i;

	if (!g_philo_states)
		return ;
	pthread_mutex_lock(&g_animation_mutex);
	printf("\033[3;1H");
	current = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		get_position(current->id, data->nb_philo, &x, &y);
		printf("\033[%d;%dH", y, x);
		draw_philosopher(current, x, y);
		current = current->next;
		i++;
	}
	draw_stats(data);
	fflush(stdout);
	pthread_mutex_unlock(&g_animation_mutex);
}

void	print_status_animated(t_philo *philo, char *status)
{
	long long	timestamp;

	if (!philo->data->flags->animate)
	{
		print_status(philo, status);
		return ;
	}
	timestamp = get_time() - philo->data->start_time;
	if (ft_strcmp(status, "is thinking") == 0)
		set_philo_state(philo, STATE_THINKING);
	else if (ft_strcmp(status, "is eating") == 0)
		set_philo_state(philo, STATE_EATING);
	else if (ft_strcmp(status, "is sleeping") == 0)
		set_philo_state(philo, STATE_SLEEPING);
	else if (ft_strcmp(status, "has taken a fork") == 0)
	{
		set_philo_state(philo, STATE_TAKING_FORK);
		g_fork_states[philo->id - 1] = true;
	}
	else if (ft_strcmp(status, "died") == 0)
		set_philo_state(philo, STATE_DEAD);
	update_animation(philo->data);
	printf("\033[%d;1H", 25 + philo->data->nb_philo);
	printf(LIGHT_GRAY "[%6lld ms] " RESET, timestamp);
	printf("Philo %d %s\n", philo->id, status);
}