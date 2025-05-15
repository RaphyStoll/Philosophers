/* ************************************************************************** */
/*                                                                            */
/*                           Test File - test: init_default_data              */
/*                                                                            */
/*   Created: 2025/05/11 21:45:59 											  */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "../header/struct.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


t_data	*init_default_data(t_data* data);
void	free_data(t_data *data);

// Nouvelle version plus lisible et explicite de compare_two_data_init
static bool compare_two_data_init(void)
{
	t_data *d1 = malloc(sizeof(t_data));
	t_data *d2 = malloc(sizeof(t_data));
	if (!d1 || !d2)
		return (printf("malloc failed\n"), false);

	if (!init_default_data(d1) || !init_default_data(d2))
	{
		printf("init_default_data failed\n");
		free_data(d1);
		free_data(d2);
		return false;
	}

	bool has_error = true;

	// Vérification des champs scalaires
	if (d1->nb_philo != d2->nb_philo)
		printf(" > FAIL: nb_philo mismatch\n"), has_error = false;
	if (d1->time_to_die != d2->time_to_die)
		printf(" > FAIL: time_to_die mismatch\n"), has_error = false;
	if (d1->time_to_eat != d2->time_to_eat)
		printf(" > FAIL: time_to_eat mismatch\n"), has_error = false;
	if (d1->time_to_sleep != d2->time_to_sleep)
		printf(" > FAIL: time_to_sleep mismatch\n"), has_error = false;
	if (d1->must_eat_count != d2->must_eat_count)
		printf(" > FAIL: must_eat_count mismatch\n"), has_error = false;
	if (d1->fed_count != d2->fed_count)
		printf(" > FAIL: fed_count mismatch\n"), has_error = false;
	if (d1->is_dead != d2->is_dead)
		printf(" > FAIL: is_dead mismatch\n"), has_error = false;
	if (d1->simulation_end != d2->simulation_end)
		printf(" > FAIL: simulation_end mismatch\n"), has_error = false;

	// Vérification des pointeurs : doivent être différents
	if (d1->flags == d2->flags)
		printf(" > FAIL: flags pointers should be different\n"), has_error = false;
	if (d1->mutex == d2->mutex)
		printf(" > FAIL: mutex pointers should be different\n"), has_error = false;

	// Vérification du contenu des flags
	if (memcmp(d1->flags, d2->flags, sizeof(t_flags)) != 0)
		printf(" > FAIL: flags content mismatch\n"), has_error = false;

	// Vérification du contenu des mutexes (seulement les booléens init)
	if (d1->mutex->print_lock_initialized != d2->mutex->print_lock_initialized)
		printf(" > FAIL: print_lock_initialized mismatch\n"), has_error = false;
	if (d1->mutex->death_mutex_initialized != d2->mutex->death_mutex_initialized)
		printf(" > FAIL: death_mutex_initialized mismatch\n"), has_error = false;
	if (d1->mutex->fed_mutex_initialized != d2->mutex->fed_mutex_initialized)
		printf(" > FAIL: fed_mutex_initialized mismatch\n"), has_error = false;

	free_data(d1);
	free_data(d2);
	return !has_error;
}

static bool	base_test(void)
{
	bool has_error = true;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("malloc failed\n");
		has_error = false;
		return (false);
	}
	if (!init_default_data(data))
	{
		printf(" > FAIL: init_default_data failed\n");
		has_error = false;
		free_data(data);
		return (false);
	}

	if (data->nb_philo != 0)
	{
		printf(" > FAIL: init nb_philo failed\n");
		has_error = false;
	}
	if (data->time_to_die != 0)
	{
		printf(" > FAIL: init time_to_die failed\n");
		has_error = false;
	}
	if (data->time_to_eat != 0)
	{
		printf(" > FAIL: init time_to_eat failed\n");
		has_error = false;
	}
	if (data->time_to_sleep != 0)
	{
		printf(" > FAIL: init time_to_sleep failed\n");
		has_error = false;
	}
	if (data->must_eat_count != -1)
	{
		printf(" > FAIL: init must_eat_count failed\n");
		has_error = false;
	}
	if (data->forks != NULL)
	{
		printf(" > FAIL: init forks should be NULL\n");
		has_error = false;
	}
	if (data->philos != NULL)
	{
		printf(" > FAIL: init philos should be NULL\n");
		has_error = false;
	}
	if (data->start_time != 0)
	{
		printf(" > FAIL: init start_time failed\n");
		has_error = false;
	}
	if (!data->mutex)
	{
		printf(" > FAIL: mutex struct not allocated\n");
		has_error = false;
	}
	else
	{
		if (!data->mutex->print_lock_initialized)
		{

			printf(" > FAIL: print_lock not initialized\n");
			has_error = false;
		}
		if (!data->mutex->death_mutex_initialized)
		{

			printf(" > FAIL: death_mutex not initialized\n");
			has_error = false;
		}
		if (!data->mutex->fed_mutex_initialized)
		{

			printf(" > FAIL: fed_mutex not initialized\n");
			has_error = false;
		}
	}
	if (!data->flags)
	{
		printf(" > FAIL: flags pointer not initialized\n");
		has_error = false;
	}
	else
	{
		if (data->flags->help != false)
		{

			printf(" > FAIL: init flags->help failed\n");
			has_error = false;
		}
		if (data->flags->debug != false)
		{

			printf(" > FAIL: init flags->debug failed\n");
			has_error = false;
		}
		if (data->flags->verbose != false)
		{

			printf(" > FAIL: init flags->verbose failed\n");
			has_error = false;
		}
		if (data->flags->animate != false)
		{
			printf(" > FAIL: init flags->animate failed\n");
			has_error = false;
		}
		if (data->flags->stats != false)
		{
			printf(" > FAIL: init flags->stats failed\n");
			has_error = false;
		}
		if (data->flags->log != false)
		{
			printf(" > FAIL: init flags->log failed\n");
			has_error = false;
		}
	}

	free_data(data);
	return (!has_error);
}

int test1(void)
{
	int failures = 0;

	RUN_SUBTEST("base_test", base_test);
	RUN_SUBTEST("compare_two_data_init", compare_two_data_init);

	return (failures);
}