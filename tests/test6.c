/* ************************************************************************** */
/*                                                                            */
/*                           Test File - test: parsing arguments              */
/*                                                                            */
/*   Created: 2025/05/24                                                      */
/*                                                                            */
/* ************************************************************************** */

// test6.c - Tests du parsing des arguments
#include "../header/struct.h"
#include "test.h"
#include <stdlib.h>

bool parsing(t_data *data, const int argc, const char **argv);
t_data *init_default_data(t_data *data);
void free_data(t_data *data);

static int test_valid_args_basic(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    const char *argv[] = {"./philo", "4", "410", "200", "200"};
    
    bool result = parsing(data, 5, argv);
    
    if (!result)
    {
        printf(" > FAIL: parsing valid basic args failed\n");
        free_data(data);
        return false;
    }
    
    if (data->nb_philo != 4 || data->time_to_die != 410 || 
        data->time_to_eat != 200 || data->time_to_sleep != 200)
    {
        printf(" > FAIL: parsed values incorrect\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

static int test_valid_args_with_eat_count(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    const char *argv[] = {"./philo", "5", "800", "200", "200", "7"};
    
    bool result = parsing(data, 6, argv);
    
    if (!result)
    {
        printf(" > FAIL: parsing with eat count failed\n");
        free_data(data);
        return false;
    }
    
    if (data->must_eat_count != 7)
    {
        printf(" > FAIL: must_eat_count not set correctly\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

static int test_invalid_args_count(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    
    // Trop peu d'arguments
    const char *argv1[] = {"./philo", "4", "410"};
    if (parsing(data, 3, argv1))
    {
        printf(" > FAIL: should reject too few arguments\n");
        free_data(data);
        return false;
    }
    
    // Trop d'arguments
    const char *argv2[] = {"./philo", "4", "410", "200", "200", "7", "extra"};
    if (parsing(data, 7, argv2))
    {
        printf(" > FAIL: should reject too many arguments\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

static int test_invalid_values(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    
    // Nombres négatifs
    const char *argv1[] = {"./philo", "-1", "410", "200", "200"};
    if (parsing(data, 5, argv1))
    {
        printf(" > FAIL: should reject negative numbers\n");
        free_data(data);
        return false;
    }
    
    // Zéro
    const char *argv2[] = {"./philo", "0", "410", "200", "200"};
    if (parsing(data, 5, argv2))
    {
        printf(" > FAIL: should reject zero philosophers\n");
        free_data(data);
        return false;
    }
    
    // Non-numérique
    const char *argv3[] = {"./philo", "abc", "410", "200", "200"};
    if (parsing(data, 5, argv3))
    {
        printf(" > FAIL: should reject non-numeric values\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

static int test_edge_values(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    
    // Trop de philosophes
    const char *argv1[] = {"./philo", "201", "410", "200", "200"};
    if (parsing(data, 5, argv1))
    {
        printf(" > FAIL: should reject too many philosophers (>200)\n");
        free_data(data);
        return false;
    }
    
    // Limite acceptable
    const char *argv2[] = {"./philo", "200", "410", "200", "200"};
    if (!parsing(data, 5, argv2))
    {
        printf(" > FAIL: should accept 200 philosophers\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

int test6(void)
{
    int failures = 0;
    
    RUN_SUBTEST("test_valid_args_basic", test_valid_args_basic);
    RUN_SUBTEST("test_valid_args_with_eat_count", test_valid_args_with_eat_count);
    RUN_SUBTEST("test_invalid_args_count", test_invalid_args_count);
    RUN_SUBTEST("test_invalid_values", test_invalid_values);
    RUN_SUBTEST("test_edge_values", test_edge_values);
    
    return failures;
}