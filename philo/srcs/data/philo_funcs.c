/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:06:50 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 11:00:48 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>
#include "table.h"
#include "utils.h"

void	philo_eat(t_philo *philo)
{
	size_t	time;

	if (philo == NULL)
		return ;
	time = get_millitime();
	print(philo->table, "%zu %d is eating\n", time, philo->number);
	set_last_eat(philo, time);
	my_usleep(philo->table->settings->time_to_eat * 1000);
	decrement_left_num_of_eat(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (philo == NULL)
		return ;
	print(philo->table, "%zu %d is sleeping\n", get_millitime(), philo->number);
	my_usleep(philo->table->settings->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (philo == NULL)
		return ;
	print(philo->table, "%zu %d is thinking\n", get_millitime(), philo->number);
}

void	take_forks(t_philo *philo)
{
	int	i;
	int	fork_num;

	if (philo == NULL)
		return ;
	i = 0;
	while (i < 2)
	{
		fork_num = philo->number + i;
		if (fork_num >= philo->table->length)
			fork_num = 0;
		while (_take(philo->table->forks[fork_num]) == false)
		{
			my_usleep(1000);
			if (is_finish(philo->table))
				return ;
		}
		print(philo->table, "%zu %d has taken a fork\n",
			get_millitime(), philo->number);
		i++;
	}
}

void	return_forks(t_philo *philo)
{
	int	i;
	int	fork_num;

	if (philo == NULL)
		return ;
	i = 0;
	while (i < 2)
	{
		fork_num = philo->number + i;
		if (fork_num >= philo->table->length)
			fork_num = 0;
		if (is_finish(philo->table))
			return ;
		_return(philo->table->forks[fork_num]);
		i++;
	}
}
