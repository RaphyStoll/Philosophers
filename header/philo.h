
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include "struct.h"

//! main
int	main(int argc, char **argv);

//! init
t_philo	*create_philos(t_data *data);
t_data	*init_default_data(t_data* data);

//! parsing
bool	parsing(t_data *data, const int argc, const char **argv);
bool	arg_verif(t_data *data, const int argc, const char **argv);

//! memory
void	free_data(t_data *data);
void	free_flags(t_flags *flags);
void	free_philo(t_philo *philo);
void	free_mutexes(t_mutexes *m);

//! utils
bool	error_msg(const char *msg);

//! mini libft
size_t	ft_strlen(const char *str);
bool	is_digit(char *str);
int		ft_strcmp(char *s1, char *s2);

//! parsing_utils
bool	is_flag(t_flags *flags, char *str);

//! print help
void	print_help(void);

#endif