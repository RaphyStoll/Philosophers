#define _GNU_SOURCE
#include "test.h"
#include "../header/struct.h"
#include <dlfcn.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

extern int __real_pthread_mutex_init(pthread_mutex_t*, const pthread_mutexattr_t*);

t_data	*init_default_data(t_data* data);
void	free_data(t_data *data);

static void	*(*real_malloc)(size_t) = NULL;
static bool	trigger_malloc_fail = false;

// Compare two t_data after init_default_data, checking scalar equality,
// pointer inequality for flags/mutex, and content equality.
bool compare_two_data_init(void)
{
	t_data *d1 = malloc(sizeof(t_data));
	t_data *d2 = malloc(sizeof(t_data));
	if (!d1 || !d2)
		return (fprintf(stderr, "malloc failed\n"), false);
	if (!init_default_data(d1) || !init_default_data(d2))
		return (fprintf(stderr, "init_default_data failed\n"), false);

	bool has_error = false;

	if (d1->nb_philo != d2->nb_philo)
		(has_error = true, fprintf(stderr, "nb_philo mismatch\n"));
	if (d1->time_to_die != d2->time_to_die)
		(has_error = true, fprintf(stderr, "time_to_die mismatch\n"));
	if (d1->time_to_eat != d2->time_to_eat)
		(has_error = true, fprintf(stderr, "time_to_eat mismatch\n"));
	if (d1->time_to_sleep != d2->time_to_sleep)
		(has_error = true, fprintf(stderr, "time_to_sleep mismatch\n"));
	if (d1->must_eat_count != d2->must_eat_count)
		(has_error = true, fprintf(stderr, "must_eat_count mismatch\n"));
	if (d1->fed_count != d2->fed_count)
		(has_error = true, fprintf(stderr, "fed_count mismatch\n"));
	if (d1->is_dead != d2->is_dead)
		(has_error = true, fprintf(stderr, "is_dead mismatch\n"));
	if (d1->simulation_end != d2->simulation_end)
		(has_error = true, fprintf(stderr, "simulation_end mismatch\n"));

	if (d1->flags == d2->flags)
		(has_error = true, fprintf(stderr, "flags pointers are equal\n"));
	if (d1->mutex == d2->mutex)
		(has_error = true, fprintf(stderr, "mutex pointers are equal\n"));

	if (memcmp(d1->flags, d2->flags, sizeof(t_flags)) != 0)
		(has_error = true, fprintf(stderr, "flags content mismatch\n"));

	if (memcmp(d1->mutex, d2->mutex, sizeof(t_mutexes)) != 0)
		(has_error = true, fprintf(stderr, "mutex content mismatch\n"));

	free_data(d1);
	free(d1);
	free_data(d2);
	free(d2);
	return (!has_error);
}

void	*malloc(size_t size)
{
	if (!real_malloc)
		real_malloc = dlsym(RTLD_NEXT, "malloc");
	if (trigger_malloc_fail && size == sizeof(t_flags))
		return (NULL);
	if (trigger_malloc_fail && size == sizeof(t_mutexes))
		return (NULL);
	return real_malloc(size);
}

int	pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
	if (trigger_malloc_fail)
		return 1;
	return __real_pthread_mutex_init(mutex, attr);
}

bool	simulate_flags_malloc_failure(void)
{
	bool result;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		fprintf(stderr, "[malloc fail test] data malloc failed\n");
		return (false);
	}
	trigger_malloc_fail = true;
	result = (init_default_data(data) == NULL);
	trigger_malloc_fail = false;
	free(data);
	if (!result)
		fprintf(stderr, "[malloc fail test] init_default_data should return NULL\n");
	return result;
}

bool	simulate_mutex_malloc_failure(void)
{
	bool result;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		fprintf(stderr, "[malloc fail test] data malloc failed\n");
		return (false);
	}
	trigger_malloc_fail = true;
	result = (init_default_data(data) == NULL);
	trigger_malloc_fail = false;
	free(data);
	if (!result)
		fprintf(stderr, "[malloc fail test] init_default_data (mutex) should return NULL\n");
	else
		write(1, "[malloc fail test] (mutex) OK\n", 30);
	return result;
}

bool	simulate_mutex_init_failure(void)
{
	bool result;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		fprintf(stderr, "[mutex init fail test] data malloc failed\n");
		return (false);
	}
	trigger_malloc_fail = true;
	result = (init_default_data(data) == NULL);
	trigger_malloc_fail = false;
	free(data);
	if (!result)
		fprintf(stderr, "[mutex init fail test] init_default_data should return NULL\n");
	else
		write(1, "[mutex init fail test] OK\n", 27);
	return result;
}

bool	base_test(void)
{
	bool has_error = false;
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		fprintf(stderr, "malloc failed\n");
		has_error = true;
		return (false);
	}
	if (!init_default_data(data))
	{
		fprintf(stderr, "init_default_data failed\n");
		has_error = true;
		free(data);
		return (false);
	}

	if (data->nb_philo != 0)
	{
		fprintf(stderr, "init nb_philo failed\n");
		has_error = true;
	}
	if (data->time_to_die != 0)
	{
		fprintf(stderr, "init time_to_die failed\n");
		has_error = true;
	}
	if (data->time_to_eat != 0)
	{
		fprintf(stderr, "init time_to_eat failed\n");
		has_error = true;
	}
	if (data->time_to_sleep != 0)
	{
		fprintf(stderr, "init time_to_sleep failed\n");
		has_error = true;
	}
	if (data->must_eat_count != -1)
	{
		fprintf(stderr, "init must_eat_count failed\n");
		has_error = true;
	}
	if (data->forks != NULL)
	{
		fprintf(stderr, "init forks should be NULL\n");
		has_error = true;
	}
	if (data->philos != NULL)
	{
		fprintf(stderr, "init philos should be NULL\n");
		has_error = true;
	}
	if (data->start_time != 0)
	{
		fprintf(stderr, "init start_time failed\n");
		has_error = true;
	}
	if (!data->mutex)
	{
		fprintf(stderr, "mutex struct not allocated\n");
		has_error = true;
	}
	else
	{
		if (!data->mutex->print_lock_initialized)
		{
			fprintf(stderr, "print_lock not initialized\n");
			has_error = true;
		}
		if (!data->mutex->death_mutex_initialized)
		{
			fprintf(stderr, "death_mutex not initialized\n");
			has_error = true;
		}
		if (!data->mutex->fed_mutex_initialized)
		{
			fprintf(stderr, "fed_mutex not initialized\n");
			has_error = true;
		}
	}
	if (!data->flags)
	{
		fprintf(stderr, "flags pointer not initialized\n");
		has_error = true;
	}
	else
	{
		if (data->flags->help != false)
		{
			fprintf(stderr, "init flags->help failed\n");
			has_error = true;
		}
		if (data->flags->debug != false)
		{
			fprintf(stderr, "init flags->debug failed\n");
			has_error = true;
		}
		if (data->flags->verbose != false)
		{
			fprintf(stderr, "init flags->verbose failed\n");
			has_error = true;
		}
		if (data->flags->animate != false)
		{
			fprintf(stderr, "init flags->animate failed\n");
			has_error = true;
		}
		if (data->flags->stats != false)
		{
			fprintf(stderr, "init flags->stats failed\n");
			has_error = true;
		}
		if (data->flags->log != false)
		{
			fprintf(stderr, "init flags->log failed\n");
			has_error = true;
		}
	}

	free_data(data);
	free(data);
	return (has_error);
}

int test4(void)
{
	int failures = 0;

	RUN_SUBTEST("base_test", base_test);
	RUN_SUBTEST("simulate_flags_malloc_failure", simulate_flags_malloc_failure);
	RUN_SUBTEST("simulate_mutex_malloc_failure", simulate_mutex_malloc_failure);
	RUN_SUBTEST("simulate_mutex_init_failure", simulate_mutex_init_failure);
	RUN_SUBTEST("compare_two_data_init", compare_two_data_init);

	return (failures);
}