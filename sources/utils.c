#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while(str[i])
		i++;
	return i;
}

int	error_msg(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}