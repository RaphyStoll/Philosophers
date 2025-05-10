#define _GNU_SOURCE
#include "test.h"
#include "../header/struct.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


t_data	*init_default_data(t_data* data);
void	free_data(t_data *data);

// Compare two t_data after init_default_data, checking scalar equality,
// pointer inequality for flags/mutex, and content equality.
bool compare_two_data_init(void)
{
	t_data *d1 = malloc(sizeof(t_data));
	t_data *d2 = malloc(sizeof(t_data));
	if (!d1 || !d2)
		return (printf("malloc failed\n"), false);
	if (!init_default_data(d1) || !init_default_data(d2))
		return (printf("init_default_data failed\n"), false);
	bool has_error = false;
	if (d1->nb_philo != d2->nb_philo)
		(has_error = true, printf("nb_philo mismatch\n"));
	if (d1->time_to_die != d2->time_to_die)
		(has_error = true, printf("time_to_die mismatch\n"));
	if (d1->time_to_eat != d2->time_to_eat)
		(has_error = true, printf("time_to_eat mismatch\n"));
	if (d1->time_to_sleep != d2->time_to_sleep)
		(has_error = true, printf("time_to_sleep mismatch\n"));
	if (d1->must_eat_count != d2->must_eat_count)
		(has_error = true, printf("must_eat_count mismatch\n"));
	if (d1->fed_count != d2->fed_count)
		(has_error = true, printf("fed_count mismatch\n"));
	if (d1->is_dead != d2->is_dead)
		(has_error = true, printf("is_dead mismatch\n"));
	if (d1->simulation_end != d2->simulation_end)
		(has_error = true, printf("simulation_end mismatch\n"));

	if (d1->flags == d2->flags)
		(has_error = true, printf("flags pointers are equal\n"));
	if (d1->mutex == d2->mutex)
		(has_error = true, printf("mutex pointers are equal\n"));

	if (d1->flags && d2->flags &&
		memcmp(d1->flags, d2->flags, sizeof(t_flags)) != 0)
		(has_error = true, printf("flags content mismatch\n"));
	else if (!d1->flags || !d2->flags)
		(has_error = true, printf("flags is NULL\n"));

	if (d1->mutex && d2->mutex &&
		memcmp(d1->mutex, d2->mutex, sizeof(t_mutexes)) != 0)
		(has_error = true, printf("mutex content mismatch\n"));
	else if (!d1->mutex || !d2->mutex)
		(has_error = true, printf("mutex is NULL\n"));

	free_data(d1);
	free_data(d2);
	return (!has_error);
}


bool	simulate_flags_malloc_failure(void)
{
	bool result;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("[malloc fail test] data malloc failed\n");
		return (false);
	}
	data->flags = NULL;
	result = (init_default_data(data) == NULL);
	free_data(data);
	if (!result)
		printf("[malloc fail test] init_default_data should return NULL\n");
	return result;
}

bool	simulate_mutex_malloc_failure(void)
{
	bool result;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("[malloc fail test] data malloc failed\n");
		return (false);
	}
	data->mutex = NULL;
	result = (init_default_data(data) == NULL);
	free_data(data);
	if (!result)
		printf("[malloc fail test] init_default_data (mutex) should return NULL\n");
	else
		write(1, "[malloc fail test] (mutex) OK\n", 30);
	return result;
}


bool	base_test(void)
{
	bool has_error = false;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("malloc failed\n");
		has_error = true;
		return (false);
	}
	if (!init_default_data(data))
	{
		printf(" > FAIL init_default_data failed\n");
		has_error = true;
		free_data(data);
		return (false);
	}

	if (data->nb_philo != 0)
	{
		printf(" > FAIL init nb_philo failed\n");
		has_error = true;
	}
	if (data->time_to_die != 0)
	{
		printf(" > FAIL init time_to_die failed\n");
		has_error = true;
	}
	if (data->time_to_eat != 0)
	{
		printf(" > FAIL init time_to_eat failed\n");
		has_error = true;
	}
	if (data->time_to_sleep != 0)
	{
		printf(" > FAIL init time_to_sleep failed\n");
		has_error = true;
	}
	if (data->must_eat_count != -1)
	{
		printf(" > FAIL init must_eat_count failed\n");
		has_error = true;
	}
	if (data->forks != NULL)
	{
		printf(" > FAIL init forks should be NULL\n");
		has_error = true;
	}
	if (data->philos != NULL)
	{
		printf(" > FAIL init philos should be NULL\n");
		has_error = true;
	}
	if (data->start_time != 0)
	{
		printf(" > FAIL init start_time failed\n");
		has_error = true;
	}
	if (!data->mutex)
	{
		printf(" > FAIL mutex struct not allocated\n");
		has_error = true;
	}
	else
	{
		if (!data->mutex->print_lock_initialized)
		{
			printf(" > FAIL print_lock not initialized\n");
			has_error = true;
		}
		if (!data->mutex->death_mutex_initialized)
		{
			printf(" > FAIL death_mutex not initialized\n");
			has_error = true;
		}
		if (!data->mutex->fed_mutex_initialized)
		{
			printf(" > FAIL fed_mutex not initialized\n");
			has_error = true;
		}
	}
	if (!data->flags)
	{
		printf(" > FAIL flags pointer not initialized\n");
		has_error = true;
	}
	else
	{
		if (data->flags->help != false)
		{
			printf(" > FAIL init flags->help failed\n");
			has_error = true;
		}
		if (data->flags->debug != false)
		{
			printf(" > FAIL init flags->debug failed\n");
			has_error = true;
		}
		if (data->flags->verbose != false)
		{
			printf(" > FAIL init flags->verbose failed\n");
			has_error = true;
		}
		if (data->flags->animate != false)
		{
			printf(" > FAIL init flags->animate failed\n");
			has_error = true;
		}
		if (data->flags->stats != false)
		{
			printf(" > FAIL init flags->stats failed\n");
			has_error = true;
		}
		if (data->flags->log != false)
		{
			printf(" > FAIL init flags->log failed\n");
			has_error = true;
		}
	}

	free_data(data);
	return (!has_error);
}

int test1(void)
{
	int failures = 0;

	RUN_SUBTEST("base_test", base_test);
	//RUN_SUBTEST("simulate_flags_malloc_failure", simulate_flags_malloc_failure);
	//RUN_SUBTEST("simulate_mutex_malloc_failure", simulate_mutex_malloc_failure);
	RUN_SUBTEST("compare_two_data_init", compare_two_data_init);

	return (failures);
}