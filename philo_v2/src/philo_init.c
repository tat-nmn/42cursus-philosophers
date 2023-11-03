/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:55:43 by tnualman          #+#    #+#             */
/*   Updated: 2023/11/03 03:24:10 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init_table_loop(t_table *table);

int	philo_check_args(int argc, char **argv)
{
	if (argc == 5)
	{
		if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
			|| ft_atoi(argv[4]) < 1 || ft_atoi(argv[1]) > MAX_PHILO)
			return (0);
	}
	else if (argc == 6)
	{
		if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
			|| ft_atoi(argv[4]) < 1 || ft_atoi(argv[5]) < 1
			|| ft_atoi(argv[1]) > MAX_PHILO)
			return (0);
	}
	else
		return (0);
	return (1);
}

void	philo_init_table(t_table *table, int argc, char **argv)
{
	table->count_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		table->max_eat = FT_INT_MAX;
	else
		table->max_eat = ft_atoi(argv[5]);
	table->there_is_dead_philo = 0;
	table->start_time = gettimeofday_ms();
	philo_init_table_loop(table);
}

static void	philo_init_table_loop(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = table->philos;
	i = -1;
	while (++i < table->count_philo)
	{
		philos[i].id = i + 1;
		philos[i].state = PHILO_THINKING;
		philos[i].count_eat = 0;
		philos[i].last_meal_time = table->start_time;
		philos[i].table = table;
		table->forks[i].state = FORK_IDLE;
	}
	i = -1;
	while (++i < table->count_philo)
		philos[i].right_fork = table->forks + i;
	while (--i > 0)
		philos[i].left_fork = table->forks + i - 1;
	philos[i--].left_fork = table->forks + table->count_philo - 1;
	while (++i < table->count_philo)
		pthread_mutex_init(&(table->forks[i].mutex), NULL);
}
