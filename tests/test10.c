/* ************************************************************************** */
/*                                                                            */
/*        Test File - test: Tests des fonctions d'affichage et de statut       */
/*                                                                            */
/*   Created: 2025/05/24 23:10:43                                             */
/*                                                                            */
/* ************************************************************************** */


// test10.c - Tests des fonctions d'affichage et de statut
#include "../header/struct.h"
#include "test.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>


bool is_simulation_running(t_data *data);
void print_status(t_philo *philo, char *status);
t_data *init_default_data(t_data *data);
void free_data(t_data *data);
long long get_time(void);
long long time_diff(long long start, long long end);
void ft_usleep(long long time);

static int test_is_simulation_running(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    
    // Au début, simulation_end = false, donc running = true
    if (!is_simulation_running(data))
    {
        printf(" > FAIL: simulation should be running initially\n");
        free_data(data);
        return false;
    }
    
    // Après avoir mis simulation_end = true
    pthread_mutex_lock(&data->mutex->death_mutex);
    data->simulation_end = true;
    pthread_mutex_unlock(&data->mutex->death_mutex);
    
    if (is_simulation_running(data))
    {
        printf(" > FAIL: simulation should not be running after end\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return false;
}

static int test_print_status_format(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    data->start_time = get_time();
    
    // Créer un philosophe de test
    t_philo philo = {0};
    philo.id = 1;
    philo.data = data;
    philo.meals_eaten = 0;
    philo.last_meal = data->start_time;
    
    // Rediriger stdout vers un fichier
    const char *tmp_path = "tmp_print.log";
    int saved_stdout = dup(STDOUT_FILENO);
    int fd = open(tmp_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        free_data(data);
        return false;
    }
    dup2(fd, STDOUT_FILENO);
    
    print_status(&philo, "is eating");
    
    fflush(stdout);
    close(fd);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    
    // Lire le fichier
    char buffer[256] = {0};
    fd = open(tmp_path, O_RDONLY);
    if (fd < 0)
    {
        free_data(data);
        return false;
    }
    read(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    unlink(tmp_path);
    
    // Vérifier le format : "timestamp id status\n"
    if (strstr(buffer, "1 is eating") == NULL)
    {
        printf(" > FAIL: wrong print format: %s\n", buffer);
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

static int test_print_status_no_overlap(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return false;
    
    init_default_data(data);
    data->start_time = get_time();
    
    // Test que print_status n'affiche rien si simulation ended
    pthread_mutex_lock(&data->mutex->death_mutex);
    data->simulation_end = true;
    pthread_mutex_unlock(&data->mutex->death_mutex);
    
    t_philo philo = {0};
    philo.id = 1;
    philo.data = data;
    
    const char *tmp_path = "tmp_print2.log";
    int saved_stdout = dup(STDOUT_FILENO);
    int fd = open(tmp_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        free_data(data);
        return false;
    }
    dup2(fd, STDOUT_FILENO);
    
    print_status(&philo, "should not print");
    
    fflush(stdout);
    close(fd);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    
    // Le fichier devrait être vide
    char buffer[256] = {0};
    fd = open(tmp_path, O_RDONLY);
    if (fd < 0)
    {
        free_data(data);
        return false;
    }
    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    unlink(tmp_path);
    
    if (bytes_read <= 0)
    {
        printf(" > FAIL: print_status should not print when simulation ended\n");
        free_data(data);
        return false;
    }
    
    free_data(data);
    return true;
}

int test10(void)
{
    int failures = 0;
    
    RUN_SUBTEST("test_is_simulation_running", test_is_simulation_running);
    RUN_SUBTEST("test_print_status_format", test_print_status_format);
    RUN_SUBTEST("test_print_status_no_overlap", test_print_status_no_overlap);

    return failures;
}