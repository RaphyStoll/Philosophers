/* ************************************************************************** */
/*                                                                            */
/*                           Test File - test: simulation edge cases          */
/*                                                                            */
/*   Created: 2025/05/24                                                      */
/*                                                                            */
/* ************************************************************************** */

// test9.c - Tests des cas limites de simulation
#include "../header/struct.h"
#include "test.h"
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

bool start_simulation(t_data *data);
bool parsing(t_data *data, const int argc, const char **argv);
t_data *init_default_data(t_data *data);
void free_data(t_data *data);
long long get_time(void);
long long time_diff(long long start, long long end);
void ft_usleep(long long time);

static int test_simulation_death_detection(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return 1;
    
    init_default_data(data);
    
    // Simulation qui doit mourir rapidement : time_to_die < time_to_eat
    const char *argv[] = {"./philo", "2", "100", "200", "50"};
    
    if (!parsing(data, 5, argv))
    {
        printf(" > FAIL: parsing failed\n");
        free_data(data);
        return false;
    }
    
    long long start = get_time();
    start_simulation(data);
    long long end = get_time();
    
    // La simulation devrait se terminer en moins de 200ms
    if (time_diff(start, end) > 200)
    {
        printf(" > FAIL: death detection too slow\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

static int test_simulation_single_philo(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    
    // Un seul philosophe devrait mourir
    const char *argv[] = {"./philo", "1", "200", "100", "100"};
    
    if (!parsing(data, 5, argv))
    {
        printf(" > FAIL: parsing failed\n");
        free_data(data);
        return false;
    }
    
    long long start = get_time();
    start_simulation(data);
    long long end = get_time();
    
    // Devrait mourir en ~200ms
    long long duration = time_diff(start, end);
    if (duration < 190 || duration > 250)
    {
        printf(" > FAIL: single philo timing wrong: %lld ms\n", duration);
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

static int test_simulation_eat_count(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return 1;
    
    init_default_data(data);
    
    // Simulation avec count : chaque philo doit manger 3 fois
    const char *argv[] = {"./philo", "2", "1000", "50", "50", "3"};
    
    if (!parsing(data, 6, argv))
    {
        printf(" > FAIL: parsing failed\n");
        free_data(data);
        return false;
    }
    
    long long start = get_time();
    start_simulation(data);
    long long end = get_time();
    
    // Devrait finir avant time_to_die mais après le temps nécessaire pour manger
    long long duration = time_diff(start, end);
    if (duration > 900) // Bien avant time_to_die
    {
        printf(" > FAIL: eat count simulation too long: %lld ms\n", duration);
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

int test9(void)
{
    int failures = 0;
    
    RUN_SUBTEST("test_simulation_death_detection", test_simulation_death_detection);
    RUN_SUBTEST("test_simulation_single_philo", test_simulation_single_philo);
    RUN_SUBTEST("test_simulation_eat_count", test_simulation_eat_count);
    
    return failures;
}