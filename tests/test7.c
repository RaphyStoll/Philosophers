/* ************************************************************************** */
/*                                                                            */
/*                           Test File - test: time functions                 */
/*                                                                            */
/*   Created: 2025/05/24                                                      */
/*                                                                            */
/* ************************************************************************** */

// test7.c - Tests des fonctions de temps
#include "test.h"
#include <unistd.h>
#include <sys/time.h>
#include <sys/time.h>
#include <stdbool.h>

long long get_time(void);
long long time_diff(long long start, long long end);
void ft_usleep(long long time);

static int test_get_time_monotonic(void)
{
    long long time1 = get_time();
    usleep(1000); // 1ms
    long long time2 = get_time();
    
    if (time2 <= time1)
    {
        printf(" > FAIL: get_time() should be monotonic\n");
        return false;
    }
    
    if (time2 - time1 > 50) // Plus de 50ms semble excessif pour 1ms d'attente
    {
        printf(" > FAIL: get_time() precision seems off\n");
        return false;
    }
    
    return true;
}

static int test_time_diff(void)
{
    long long start = 1000;
    long long end = 1500;
    long long diff = time_diff(start, end);
    
    if (diff != 500)
    {
        printf(" > FAIL: time_diff(1000, 1500) = %lld, expected 500\n", diff);
        return false;
    }
    
    // Test avec des valeurs réelles
    start = get_time();
    usleep(5000); // 5ms
    end = get_time();
    diff = time_diff(start, end);
    
    if (diff < 3 || diff > 20) // Entre 3ms et 20ms acceptable
    {
        printf(" > FAIL: time_diff real test = %lld ms, expected ~5ms\n", diff);
        return false;
    }
    
    return true;
}

static int test_ft_usleep_precision(void)
{
    long long start = get_time();
    ft_usleep(10); // 10ms
    long long end = get_time();
    long long actual = time_diff(start, end);
    
    // Tolérance de ±3ms
    if (actual < 7 || actual > 15)
    {
        printf(" > FAIL: ft_usleep(10) took %lld ms\n", actual);
        return false;
    }
    
    return true;
}

int test7(void)
{
    int failures = 0;
    
    RUN_SUBTEST("test_get_time_monotonic", test_get_time_monotonic);
    RUN_SUBTEST("test_time_diff", test_time_diff);
    RUN_SUBTEST("test_ft_usleep_precision", test_ft_usleep_precision);
    
    return failures;
}