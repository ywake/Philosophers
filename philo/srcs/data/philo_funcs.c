/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:06:50 by ywake             #+#    #+#             */
/*   Updated: 2022/01/10 23:55:34 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>
#include "table.h"
#include "utils.h"

void	philo_eat(t_philo *philo)
{
	size_t	time;

	if (is_someone_died(philo->table))
		return ;
	time = get_millitime();
	printf("%zu %d is eating\n", time, philo->number);
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->mutex);
	my_usleep(philo->table->settings->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	if (is_someone_died(philo->table))
		return ;
	printf("%zu %d is sleeping\n", get_millitime(), philo->number);
	my_usleep(philo->table->settings->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (is_someone_died(philo->table))
		return ;
	printf("%zu %d is thinking\n", get_millitime(), philo->number);
}

void	take_forks(t_philo *philo)
{
	int					i;
	int					fork_num;
	enum e_fork_dir		dir;

	i = 0;
	while (i < 2)
	{
		dir = i;
		fork_num = philo->number + dir;
		if (fork_num >= philo->table->length)
			fork_num = 0;
		while (!is_someone_died(philo->table)
			&& _take(philo->table->forks[fork_num]) == false)
			my_usleep(1000);
		if (is_someone_died(philo->table))
			return ;
		printf("%zu %d has taken a fork\n", get_millitime(), philo->number);
		i++;
	}
}

void	return_forks(t_philo *philo)
{
	int					i;
	int					fork_num;
	enum e_fork_dir		dir;

	i = 0;
	while (i < 2)
	{
		dir = i;
		fork_num = philo->number + dir;
		if (fork_num >= philo->table->length)
			fork_num = 0;
		if (is_someone_died(philo->table))
			return ;
		_return(philo->table->forks[fork_num]);
		i++;
	}
}
