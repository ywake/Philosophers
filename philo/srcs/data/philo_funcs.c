/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:48:33 by ywake             #+#    #+#             */
/*   Updated: 2022/01/28 02:05:06 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include <stdio.h>

t_timestamp	take_a_fork(t_philo *philo, int fork_num)
{
	bool	is_success;

	is_success = try_take_a_fork(philo->table->forks[fork_num]);
	if (!is_success)
		return (-1000);
	if (!philo->table->finish)
		printf("%zu %d has taken a fork\n", get_timestamp(), philo->number + 1);
	return (0);
}

/**
 * Return Value
 * Success: 0
 * Failure: -(retry time)
 */
t_timestamp	take_right_fork(t_philo *philo)
{
	int	fork_num;

	fork_num = philo->number;
	return (take_a_fork(philo, fork_num));
}

/**
 * Return Value
 * Success: 0
 * Failure: -(retry time)
 */
t_timestamp	take_left_fork(t_philo *philo)
{
	int	fork_num;

	fork_num = (philo->number + 1) % philo->settings->num_of_philos;
	return (take_a_fork(philo, fork_num));
}

t_timestamp	philo_eat(t_philo *philo)
{
	t_timestamp	now;

	now = get_timestamp();
	printf("%zu %d is eating\n", now, philo->number + 1);
	philo->last_eat = now;
	if (philo->left_num_of_eat > 0)
		philo->left_num_of_eat--;
	return (philo->settings->time_to_eat * 1000);
}

t_timestamp	philo_sleep(t_philo *philo)
{
	int	i;
	int	fork_num;

	i = 0;
	while (i < 2)
	{
		fork_num = (philo->number + i) % philo->table->length;
		drop_a_fork(philo->table->forks[fork_num]);
		i++;
	}
	printf("%zu %d is sleeping\n", get_timestamp(), philo->number + 1);
	return (philo->settings->time_to_sleep * 1000);
}
