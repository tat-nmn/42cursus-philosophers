/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:25:37 by tnualman          #+#    #+#             */
/*   Updated: 2023/10/31 18:52:58 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_join_destroy(pthread_t philo_thread, pthread_mutex_t *fork)
{
	pthread_join(philo_thread, NULL);
	pthread_mutex_destroy(fork);
}

int	main(int argc, char **argv)
{
	int		i;
	t_table	table;

	if (!philo_check_args(argc, argv))
    {
        printf("Error: invalid argument(s)!");
        return (0);
    }
	philo_init_table(&table, argc, argv);
	i = -1;
    while (++i < table.count_philo)
		if (i % 2 == 0)
			pthread_create(&((table.philos)[i].philo_thread), NULL,
				&philo_routine, &table);
	usleep(TIME_INCREMENT);
	while (--i >= 0)
		if (i % 2 == 1)
			pthread_create(&((table.philos)[i].philo_thread), NULL,
				&philo_routine, &table);
	while (++i < table.count_philo))
		philo_join_destroy(philo[(table.philos)[i].philo_thread,
			table.forks + i);
	return (0);
}