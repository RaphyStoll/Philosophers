/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:00:00 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/24 15:19:41 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "philo.h"
# include "colors.h"

# define CLEAR_SCREEN "\033[2J"
# define CURSOR_HOME "\033[H"
# define HIDE_CURSOR "\033[?25l"
# define SHOW_CURSOR "\033[?25h"

typedef enum e_philo_state
{
	STATE_THINKING,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_TAKING_FORK,
	STATE_DEAD
}	t_philo_state;

//! animation
void	init_animation(t_data *data);
void	update_animation(t_data *data);
void	cleanup_animation(void);
void	print_status_animated(t_philo *philo, char *status);
void	set_philo_state(t_philo *philo, t_philo_state state);

//! animation utils
void	draw_table(t_data *data);
void	draw_philosopher(t_philo *philo, int pos_x, int pos_y);
void	draw_fork(int fork_id, bool taken, int pos_x, int pos_y);
void	draw_stats(t_data *data);

#endif