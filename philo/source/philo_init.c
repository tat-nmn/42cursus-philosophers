/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:55:43 by tnualman          #+#    #+#             */
/*   Updated: 2023/10/31 20:14:20 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init_table_loop();

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
	int	i;

	table->count_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		table->count_eat = INT_MAX;
	else
		table->count_eat = ft_atoi(argv[5])
	i = -1;
	
	while (++i < table->count_philo)
	{
		philos[i].id = i + 1;
		philos[i].state = STATE_THINKING;
		philos[i].taken_left_fork = 0;
		philos[i].taken_right_fork = 0;
		pthread_mutex_init(table->forks + i, NULL);
	}
	i = -1;
	while (++i < table->count_philo)
		philos[i].right_fork = table->forks + i;
	while (--i > 0)
		philos[i].left_fork = table->forks + i - 1;
	philos[0].left_fork = table->forks + table->count_philo - 1;
}
