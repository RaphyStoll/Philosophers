
#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long long       last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data   *data;
    struct s_philo  *next;
}   t_philo;

typedef struct s_data
{
    int             nb_philo;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int             must_eat_count;

    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;

    long long       start_time;
    t_philo         *philos;
}   t_data;


t_philo	*create_philos(t_data *data);
bool	parse_arg(int argc, char **argv);

#endif