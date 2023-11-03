/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:50:15 by tnualman          #+#    #+#             */
/*   Updated: 2023/11/03 19:04:24 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gettimeofday_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
}

int	philo_someone_died(t_table *table, t_philo *philo)
{
	if (table->there_is_dead_philo)
		return (1);
	if (gettimeofday_ms() >= philo->last_meal_time + table->time_die)
	{
		philo->state = PHILO_DIED;
		table->there_is_dead_philo = 1;
		return (1);
	}
	return (0);
}

void	philo_print(t_philo *philo, int action)
{
	unsigned long	time_ms;

	pthread_mutex_lock(&(philo->table->mutex_printf));
	time_ms = gettimeofday_ms() - philo->table->start_time;
	if (action == PHILO_THINKING && philo->state != PHILO_THINKING)
	{
		printf("%8lu %3d is thinking\n", time_ms, philo->id);
		philo->state = PHILO_THINKING;
	}
	philo->state = action;
	if (action == PHILO_TAKE_FORK)
		printf("%8lu %3d has taken a fork\n", time_ms, philo->id);
	if (action == PHILO_EATING)
		printf("%8lu %3d is eating\n", time_ms, philo->id);
	if (action == PHILO_SLEEPING)
		printf("%8lu %3d is sleeping\n", time_ms, philo->id);
	if (action == PHILO_DIED)
		printf("%8lu %3d died\n", time_ms, philo->id);
	pthread_mutex_unlock(&(philo->table->mutex_printf));
}
