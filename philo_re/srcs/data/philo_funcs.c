/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:48:33 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 19:00:15 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include <stdio.h>

t_timestamp	take_right_fork(t_philo *philo)
{
	int	fork_num;

	fork_num = philo->number;
	while (!(philo->table->finish || try_take(philo->table->forks[fork_num])))
	{
		pthread_mutex_unlock(&philo->table->mutex);
		my_usleep(1000);
		pthread_mutex_lock(&philo->table->mutex);
	}
	if (philo->table->finish)
		return (0);
	printf("%zu %d has taken a fork\n", get_timestamp(), philo->number + 1);
	return (0);
}

t_timestamp	take_left_fork(t_philo *philo)
{
	int	fork_num;

	fork_num = (philo->number + 1) % philo->settings->num_of_philos;
	while (!(philo->table->finish || try_take(philo->table->forks[fork_num])))
	{
		pthread_mutex_unlock(&philo->table->mutex);
		my_usleep(1000);
		pthread_mutex_lock(&philo->table->mutex);
	}
	if (philo->table->finish)
		return (0);
	printf("%zu %d has taken a fork\n", get_timestamp(), philo->number + 1);
	return (0);
}

t_timestamp	philo_eat(t_philo *philo)
{
	t_timestamp	now;

	now = get_timestamp();
	printf("%zu %d is eating\n", now, philo->number + 1);
	philo->last_eat = now;
	return (philo->settings->time_to_eat * 1000);
}

t_timestamp	philo_sleep(t_philo *philo)
{
	printf("%zu %d is sleeping\n", get_timestamp(), philo->number + 1);
	return (philo->settings->time_to_sleep * 1000);
}

t_timestamp	philo_think(t_philo *philo)
{
	printf("%zu %d is thinking\n", get_timestamp(), philo->number + 1);
	return (0);
}
