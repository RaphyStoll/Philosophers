/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:25 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/29 19:10:33 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colors.h"

bool	error_msg(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (false);
}
