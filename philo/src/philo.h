/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:09:10 by tnualman          #+#    #+#             */
/*   Updated: 2023/11/03 19:06:30 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILO			200
# define PHILO_THINKING		1
# define PHILO_TAKE_FORK	2
# define PHILO_EATING		4
# define PHILO_SLEEPING		8
# define PHILO_DIED			0
# define FORK_IDLE			0
# define FORK_LEFT			1
# define FORK_RIGHT			2
# define USEC_INCREMENT		100
# define FT_INT_MAX			0x7FFFFFFF

typedef struct s_fork
{
	int				state;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				state;
	int				count_eat;
	unsigned long	last_meal_time;
	pthread_t		philo_thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				count_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_eat;
	int				there_is_dead_philo;
	unsigned long	start_time;
	t_philo			philos[MAX_PHILO];
	t_fork			forks[MAX_PHILO];
	pthread_mutex_t	mutex_printf;
}	t_table;

// ft_atoi.c
int				ft_atoi(const char *str);

// philo_utils.c
unsigned long	gettimeofday_ms(void);
int				philo_someone_died(t_table *table, t_philo *philo);
void			philo_init_time(t_philo *philo);
void			philo_print(t_philo *philo, int action);

// philo_init.c
int				philo_check_args(int argc, char **argv);
void			philo_init_table(t_table *table, int argc, char **argv);

// philo_routine.c
void			*philo_routine(void *args);

#endif
