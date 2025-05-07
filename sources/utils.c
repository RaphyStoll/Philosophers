/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:01:39 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/07 16:25:55 by raphaelferr      ###   ########.fr       */
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
