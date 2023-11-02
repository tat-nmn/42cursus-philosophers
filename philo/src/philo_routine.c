/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:10:28 by tnualman          #+#    #+#             */
/*   Updated: 2023/11/03 03:34:01 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_take_fork(t_philo *philo, int which);
static void	philo_return_fork(t_philo *philo, int which);
static void	philo_eat_sleep(t_table *table, t_philo *philo);
static void	philo_dead_cleanup(t_table *table, t_philo *philo);

void	*philo_routine(void *args)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)args;
	table = philo->table;
	while ((philo->count_eat < table->max_eat)
		&& !philo_someone_died(table, philo))
	{
		philo_print(philo, PHILO_THINKING);
		if (philo->left_fork->state == FORK_IDLE)
			philo_take_fork(philo, FORK_LEFT);
		if (philo->right_fork->state == FORK_IDLE)
			philo_take_fork(philo, FORK_RIGHT);
		if (philo->left_fork->state == philo->id
			&& philo->right_fork->state == philo->id
			&& philo->left_fork != philo->right_fork)
			philo_eat_sleep(table, philo);
	}
	if (philo_someone_died(table, philo))
		philo_dead_cleanup(table, philo);
	return (NULL);
}

static void	philo_take_fork(t_philo *philo, int which)
{
	if (which == FORK_LEFT)
	{
		pthread_mutex_lock(&(philo->left_fork->mutex));
		philo->left_fork->state = philo->id;
	}
	if (which == FORK_RIGHT)
	{
		pthread_mutex_lock(&(philo->right_fork->mutex));
		philo->right_fork->state = philo->id;
	}
	philo_print(philo, PHILO_TAKE_FORK);
}

static void	philo_return_fork(t_philo *philo, int which)
{
	if (which == FORK_LEFT)
	{
		philo->left_fork->state = FORK_IDLE;
		pthread_mutex_unlock(&(philo->left_fork->mutex));
	}
	if (which == FORK_RIGHT)
	{
		philo->right_fork->state = FORK_IDLE;
		pthread_mutex_unlock(&(philo->right_fork->mutex));
	}
}

static void	philo_eat_sleep(t_table *table, t_philo *philo)
{
	philo->last_meal_time = gettimeofday_ms();
	philo_print(philo, PHILO_EATING);
	while (gettimeofday_ms() < (philo->last_meal_time + table->time_eat))
	{
		usleep(USEC_INCREMENT);
		if (philo_someone_died(table, philo))
			return ;
	}
	philo->count_eat++;
	philo_return_fork(philo, FORK_LEFT);
	philo_return_fork(philo, FORK_RIGHT);
	philo_print(philo, PHILO_SLEEPING);
	while (gettimeofday_ms() < (philo->last_meal_time + table->time_eat
			+ table->time_sleep))
	{
		usleep(USEC_INCREMENT);
		if (philo_someone_died(table, philo))
			return ;
	}
}

static void	philo_dead_cleanup(t_table *table, t_philo *philo)
{
	if (philo->state == PHILO_DIED
		|| gettimeofday_ms() >= philo->last_meal_time + table->time_die)
		philo_print(philo, PHILO_DIED);
	if (philo->left_fork->state == philo->id)
		philo_return_fork(philo, FORK_LEFT);
	if (philo->right_fork->state == philo->id)
		philo_return_fork(philo, FORK_RIGHT);
}
