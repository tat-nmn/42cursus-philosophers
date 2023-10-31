/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:10:28 by tnualman          #+#    #+#             */
/*   Updated: 2023/10/31 20:14:37 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	init_time(philo);
	while (philo->prop.n_eat && !is_die(philo))
	{
		print_log(philo, STATE_THINKING);
		if ((philo->forks[philo->id - 1] == IDLE || philo->forks[philo->id - 1]
				== philo->id) && !is_die(philo))
		{
			if (philo->forks[philo->id - 1] == IDLE)
				take_left_fork(philo);
			if (!philo->forks[philo->id % philo->prop.n_phi] && !is_die(philo))
			{
				if (eat_sleep(philo, &philo->prop.n_eat))
					break ;
			}
			else
				continue ;
		}
	}
	if (is_die(philo))
		do_after_dead(philo);
	return (NULL);
}

static int	eat_sleep(t_philo *philo, int *n_eat)
{
	pthread_mutex_lock(&(philo->mtx_forks[philo->id % philo->prop.n_phi]));
	philo->forks[philo->id % philo->prop.n_phi] = philo->id;
	print_log(philo, FORK_TAKEN);
	philo->lm_time = current_time();
	print_log(philo, STATE_EATING);
	while (current_time() < (philo->lm_time + philo->prop.t_eat))
	{
		usleep(STEP);
		if (is_die(philo))
			return (1);
	}
	*n_eat = *n_eat - 1;
	philo->forks[philo->id % philo->prop.n_phi] = 0;
	pthread_mutex_unlock(&(philo->mtx_forks[philo->id % philo->prop.n_phi]));
	philo->forks[philo->id - 1] = 0;
	pthread_mutex_unlock(&(philo->mtx_forks[philo->id - 1]));
	print_log(philo, STATE_SLEEPING);
	while (current_time() < (philo->lm_time + philo->prop.t_eat
			+ philo->prop.t_sleep))
	{
		usleep(STEP);
		if (is_die(philo))
			return (1);
	}
	return (0);
}

static void	do_after_dead(t_philo *philo)
{
	if (current_time() >= philo->lm_time + (unsigned long) philo->prop.t_die)
		print_log(philo, STATE_DEAD);
	if (philo->forks[philo->id - 1] == philo->id)
	{
		philo->forks[philo->id - 1] = STATE_DEAD;
		pthread_mutex_unlock(&(philo->mtx_forks[philo->id - 1]));
	}
	if (philo->forks[philo->id % philo->prop.n_phi] == philo->id)
	{
		philo->forks[philo->id % philo->prop.n_phi] = 0;
		pthread_mutex_unlock(&(philo->mtx_forks[philo->id
				% philo->prop.n_phi]));
	}
	pthread_mutex_lock(&(philo->mtx_forks[MAX_PHILO]));
	philo->forks[MAX_PHILO] = STATE_DEAD;
	pthread_mutex_unlock(&(philo->mtx_forks[MAX_PHILO]));
}

static void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mtx_forks[philo->id - 1]));
	philo->forks[philo->id - 1] = philo->id;
	print_log(philo, FORK_TAKEN);
}
