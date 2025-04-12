#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int test1(void)
{
	t_data	data;
	t_philo	*philo;
	t_philo	*tmp;
	int		i;
	int		count;

	memset(&data, 0, sizeof(t_data));
	data.nb_philo = 5;

	data.forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo);
	if (!data.forks)
		return (1);
	for (i = 0; i < data.nb_philo; i++)
		pthread_mutex_init(&data.forks[i], NULL);

	philo = create_philos(&data);
	if (!philo)
	{
		free(data.forks);
		return (1);
	}

	// Vérification de la circularité et des IDs
	tmp = philo;
	count = 0;
	while (tmp && count < data.nb_philo)
	{
		if (tmp->id != count + 1)
		{
			fprintf(stderr, "❌ Bad ID at position %d: got %d\n", count, tmp->id);
			return (1);
		}
		if (!tmp->left_fork || !tmp->right_fork)
		{
			fprintf(stderr, "❌ Missing fork at philo %d\n", tmp->id);
			return (1);
		}
		tmp = tmp->next;
		count++;
	}
	if (tmp != philo || count != data.nb_philo)
	{
		fprintf(stderr, "❌ List is not circular or count mismatch\n");
		return (1);
	}

	// Clean up
	tmp = philo;
	for (i = 0; i < data.nb_philo; i++)
	{
		t_philo *next = tmp->next;
		free(tmp);
		tmp = next;
	}
	for (i = 0; i < data.nb_philo; i++)
		pthread_mutex_destroy(&data.forks[i]);
	free(data.forks);

	return (0);
}
