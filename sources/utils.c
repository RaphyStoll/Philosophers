/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:05:25 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/25 15:20:15 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colors.h"

bool	error_msg(const char *msg)
{
	(void)msg;
	//write(2, msg, ft_strlen(msg));
	//write(2, "\n", 1);
	return (false);
}
