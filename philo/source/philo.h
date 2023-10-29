/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:09:10 by tnualman          #+#    #+#             */
/*   Updated: 2023/10/29 22:23:18 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define MAX_PHILO				200
# define STATE_THINKING			1
# define STATE_EATING			2
# define STATE_SLEEPING			4
# define STATE_DEAD				0
# define TIME_INCREMENT			50

typedef struct s_philo
{
	int				id;
	pthread_t		philo_thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				state;
	int				taken_left_fork;
	int				taken_right_fork;
	unsigned long	start_time;
	unsigned long	last_meal_time;
}	t_philo;

// s_prop
typedef struct s_table
{
	int				count_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				count_eat;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
}	t_table;

/* init.c*/
int				check_argv(int argc, char *argv[]);
void			init_mutex(pthread_mutex_t *forks, char **argv);
void			philo_copy(t_philo *ptr, char *argv[], unsigned char *forks,
					pthread_mutex_t *mutex_forks);
void			philo_copy2(t_philo *ptr, char *argv[], int argc, int id);

/* ft_atoi.c */
int				ft_atoi(const char *str);

/* pthread.c*/
void			*philo_odd(void *args);

/* utils.c*/
unsigned long	current_time(void);
int				is_die(t_philo *philo);
void			init_time(t_philo *philo);
void			print_log(t_philo *philo, int state);

#endif
