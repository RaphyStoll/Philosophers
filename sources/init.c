#include "philo.h"

static t_philo	*init_philo(t_data *data, int i)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = i + 1;
	new->meals_eaten = 0;
	new->data = data;
	new->last_meal = 0;
	new->left_fork = &data->forks[i];
	new->right_fork = &data->forks[(i + 1) % data->nb_philo];
	new->next = NULL;
	return (new);
}

t_philo	*create_philos(t_data *data)
{
	t_philo	*first;
	t_philo	*prev;
	t_philo	*new;
	int		i;

	first = NULL;
	prev = NULL;
	i = 0;
	while (i < data->nb_philo)
	{
		new = init_philo(data, i);
		if (!new)
			return (NULL);
		if (!first)
			first = new;
		else
			prev->next = new;
		prev = new;
		i++;
	}
	if (prev)
		prev->next = first;
	return (first);
}
