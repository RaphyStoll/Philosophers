/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:08:38 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/11 23:31:44 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_flag(t_flags *flags, char *str)
{
	if (!flags)
		return (false);
	if (!str)
		return (false);
	if (!ft_strcmp(str, "--help") || !ft_strcmp(str, "-h"))
		return (flags->help = true, print_help(), true);
	else if (!ft_strcmp(str, "--debug") || !ft_strcmp(str, "-d"))
		return (true);
	else if (!ft_strcmp(str, "--verbose") || !ft_strcmp(str, "-v"))
		return (true);
	else if (!ft_strcmp(str, "--animate") || !ft_strcmp(str, "-a"))
		return (true);
	else if (!ft_strcmp(str, "--stats") || !ft_strcmp(str, "-s"))
		return (true);
	else if (!ft_strcmp(str, "--log") || !ft_strcmp(str, "-l"))
		return (true);
	return (false);
}
