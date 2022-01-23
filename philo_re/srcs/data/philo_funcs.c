/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:48:33 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 11:51:45 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include <stdio.h>

t_timestamp	take_right_fork(t_philo **philo)
{
	int	fork_num;

	if (!*philo)
		return (0);
	fork_num = (*philo)->number;
	while (*philo && (*philo)->table
		&& try_take((*philo)->table->forks[fork_num]) == false)
	{
		if (*philo && (*philo)->table)
			pthread_mutex_unlock(&(*philo)->table->mutex);
		my_usleep(1000);
		if (*philo && (*philo)->table)
			pthread_mutex_lock(&(*philo)->table->mutex);
	}
	if (*philo)
		printf("%zu %d has taken a fork\n",
			get_timestamp(), (*philo)->number + 1);
	return (0);
}

t_timestamp	take_left_fork(t_philo **philo)
{
	int	fork_num;

	if (!*philo)
		return (0);
	fork_num = ((*philo)->number + 1) % (*philo)->settings->num_of_philos;
	while (*philo && (*philo)->table && (*philo)->table->forks
		&& try_take((*philo)->table->forks[fork_num]) == false)
	{
		if (*philo && (*philo)->table)
			pthread_mutex_unlock(&(*philo)->table->mutex);
		my_usleep(1000);
		if (*philo && (*philo)->table)
			pthread_mutex_lock(&(*philo)->table->mutex);
	}
	if (*philo)
		printf("%zu %d has taken a fork\n",
			get_timestamp(), (*philo)->number + 1);
	return (0);
}

t_timestamp	philo_eat(t_philo **philo)
{
	t_timestamp	now;

	if (!*philo)
		return (0);
	now = get_timestamp();
	printf("%zu %d is eating\n", now, (*philo)->number + 1);
	(*philo)->last_eat = now;
	return ((*philo)->settings->time_to_eat * 1000);
}

t_timestamp	philo_sleep(t_philo **philo)
{
	if (!*philo)
		return (0);
	printf("%zu %d is sleeping\n", get_timestamp(), (*philo)->number + 1);
	return ((*philo)->settings->time_to_sleep * 1000);
}

t_timestamp	philo_think(t_philo **philo)
{
	if (!*philo)
		return (0);
	printf("%zu %d is thinking\n", get_timestamp(), (*philo)->number + 1);
	return (0);
}
