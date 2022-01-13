/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:06:50 by ywake             #+#    #+#             */
/*   Updated: 2022/01/13 17:28:05 by ywake            ###   ########.fr       */
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
	time = get_timestamp();
	print(philo->table, "%zu %d is eating\n", time, philo->number);
	philo->last_eat = time;
	my_usleep(philo->table->settings->time_to_eat * 1000);
	philo->num_of_eat++;
	return_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (philo == NULL)
		return ;
	print(philo->table, "%zu %d is sleeping\n", get_timestamp(), philo->number);
	my_usleep(philo->table->settings->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (philo == NULL)
		return ;
	print(philo->table, "%zu %d is thinking\n", get_timestamp(), philo->number);
}

void	take_forks(t_philo *philo)
{
	int	i;

	if (philo == NULL)
		return ;
	i = 0;
	while (i < 2)
	{
		catch_err(sem_wait(philo->table->forks));
		print(philo->table, "%zu %d has taken a fork\n",
			get_timestamp(), philo->number);
		i++;
	}
}

void	return_forks(t_philo *philo)
{
	int	i;

	if (philo == NULL)
		return ;
	i = 0;
	while (i < 2)
	{
		catch_err(sem_post(philo->table->forks));
		i++;
	}
}
