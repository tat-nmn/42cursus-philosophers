/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:50:15 by tnualman          #+#    #+#             */
/*   Updated: 2023/10/31 19:11:00 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gettimeofday_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
}

int	philo_is_dead(t_table *table, t_philo *philo)
{
	if ((gettimeofday_ms() >= philo->last_meal_time
			+ (unsigned long) table->time_die) || philo->state == STATE_DEAD)
		return (1);
	return (0);
}

void	philo_init_time(t_philo *philo)
{
	unsigned long	time_ms;

	time_ms = gettimeofday_ms();
	philo->start_time = time_ms;
	philo->last_meal_time = time_ms;
}

void	philo_print(t_table *table, t_philo *philo, int state)
{
	unsigned long	time_ms;

	time_ms = gettimeofday_ms() - (unsigned long) philo->s_time;
	if (state == FORK_TAKEN)
	{
		printf("%20lu %3d has taken a fork\n", time_ms, philo->id);
	}
	else if (state == STATE_THINKING && philo->state != STATE_THINKING)
	{
		printf("%5lu %3d is thinking\n", time_ms, philo->id);
		philo->state = STATE_THINKING;
	}
	else if (state == STATE_EATING)
		printf("%20lu %3d is eating\n", time_ms, philo->id);
	else if (state == STATE_SLEEPING)
		printf("%20lu %3d is sleeping\n", time_ms, philo->id);
	else if (state == STATE_DEAD)
		printf("%20lu %3d died\n", time_ms, philo->id);
}
