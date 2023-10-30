/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:25:37 by tnualman          #+#    #+#             */
/*   Updated: 2023/10/30 20:31:48 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_destroy(pthread_t philo, pthread_mutex_t *mutex_forks)
{
	pthread_join(philo, NULL);
	pthread_mutex_destroy(mutex_forks);
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
    while (++i < table->count_philo)
		if (i % 2 == 1)
			pthread_create(&philo[i], NULL, &philo_odd, &phi_t[i]);
	usleep(TIME_INCREMENT);
	while (--i > 0)
		if (i % 2 == 0)
			pthread_create(&philo[i - 1], NULL, &philo_odd, &phi_t[i - 1]);
	while (++i <= ft_atoi(argv[1]))
		join_destroy(philo[i - 1], &mutex_forks[i - 1]);
	return (0);
}