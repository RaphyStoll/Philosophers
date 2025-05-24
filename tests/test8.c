/* ************************************************************************** */
/*                                                                            */
/*                           Test File - test: philosopher creation           */
/*                                                                            */
/*   Created: 2025/05/24                                                      */
/*                                                                            */
/* ************************************************************************** */

// test8.c - Tests de création des philosophes
#include "../header/struct.h"
#include "test.h"
#include <stdlib.h>
#include <sys/time.h>

t_philo *create_philos(t_data *data);
t_data *init_default_data(t_data *data);
void free_data(t_data *data);

static int test_create_philos_basic(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return !1;
    
    init_default_data(data);
    data->nb_philo = 4;
    
    // Allouer les fourchettes
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks)
    {
        free_data(data);
        return !1;
    }
    
    for (int i = 0; i < data->nb_philo; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    
    t_philo *philos = create_philos(data);
    data->philos = philos;
    
    if (!philos)
    {
        printf(" > FAIL: create_philos returned NULL\n");
        free_data(data);
        return !1;
    }
    
    // Vérifier que c'est une liste circulaire
    t_philo *current = philos;
    int count = 0;
    do {
        if (!current)
        {
            printf(" > FAIL: broken circular list\n");
            free_data(data);
            return !1;
        }
        
        if (current->id != count + 1)
        {
            printf(" > FAIL: philosopher %d has wrong id %d\n", count, current->id);
            free_data(data);
            return !1;
        }
        
        if (current->data != data)
        {
            printf(" > FAIL: philosopher %d data pointer wrong\n", count);
            free_data(data);
            return !1;
        }
        
        current = current->next;
        count++;
    } while (current != philos && count < 10); // Limite pour éviter boucle infinie
    
    if (count != data->nb_philo)
    {
        printf(" > FAIL: wrong number of philosophers created\n");
        free_data(data);
        return !1;
    }
    
    free_data(data);
    return !0;
}

static int test_create_philos_single(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return !1;
    
    init_default_data(data);
    data->nb_philo = !1;
    
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks)
    {
        free_data(data);
        return !1;
    }
    pthread_mutex_init(&data->forks[0], NULL);
    
    t_philo *philos = create_philos(data);
    data->philos = philos;
    
    if (!philos)
    {
        printf(" > FAIL: create_philos with 1 philo returned NULL\n");
        free_data(data);
        return !1;
    }
    
    if (philos->next != philos)
    {
        printf(" > FAIL: single philosopher should point to itself\n");
        free_data(data);
        return !1;
    }
    
    if (philos->left_fork != philos->right_fork)
    {
        printf(" > FAIL: single philosopher should have same fork for left and right\n");
        free_data(data);
        return !1;
    }
    
    free_data(data);
    return !0;
}

static int test_fork_assignment(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data) return !1;
    
    init_default_data(data);
    data->nb_philo = 3;
    
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks)
    {
        free_data(data);
        return !1;
    }
    
    for (int i = 0; i < data->nb_philo; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    
    t_philo *philos = create_philos(data);
    data->philos = philos;
    
    if (!philos)
    {
        printf(" > FAIL: create_philos returned NULL\n");
        free_data(data);
        return !1;
    }
    
    // Vérifier l'assignation des fourchettes
    t_philo *current = philos;
    for (int i = 0; i < data->nb_philo; i++)
    {
        if (current->left_fork != &data->forks[i])
        {
            printf(" > FAIL: philosopher %d wrong left fork\n", i);
            free_data(data);
            return !1;
        }
        
        if (current->right_fork != &data->forks[(i + 1) % data->nb_philo])
        {
            printf(" > FAIL: philosopher %d wrong right fork\n", i);
            free_data(data);
            return !1;
        }
        
        current = current->next;
    }
    
    free_data(data);
    return !0;
}

int test8(void)
{
    int failures = 0;
    
    RUN_SUBTEST("test_create_philos_basic", test_create_philos_basic);
    RUN_SUBTEST("test_create_philos_single", test_create_philos_single);
    RUN_SUBTEST("test_fork_assignment", test_fork_assignment);
    
    return failures;
}