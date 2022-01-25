/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:47:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 23:37:36 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include "table.h"
#include "utils.h"

t_timestamp	philo_eat(t_philo *philo)
{
	t_timestamp	time;
	bool		is_enough;

	if (philo == NULL)
		return (0);
	time = get_timestamp();
	philo->last_eat = time;
	print(philo->table, "%zd %d is eating\n", time, philo->number);
	philo->num_of_eat++;
	is_enough = philo->num_of_eat == philo->settings->target_num_of_eat;
	if (is_enough)
		catch_err(sem_post(philo->table->num_of_finish_philos));
	return (philo->settings->time_to_eat * 1000);
}

t_timestamp	philo_sleep(t_philo *philo)
{
	if (philo == NULL)
		return (0);
	return_forks(philo);
	print(philo->table, "%zd %d is sleeping\n", get_timestamp(), philo->number);
	return (philo->settings->time_to_sleep * 1000);
}

t_timestamp	philo_think(t_philo *philo)
{
	if (philo == NULL)
		return (0);
	print(philo->table, "%zd %d is thinking\n", get_timestamp(), philo->number);
	return (0);
}

t_timestamp	take_forks(t_philo *philo)
{
	int	i;

	if (philo == NULL)
		return (0);
	i = 0;
	while (i < 2)
	{
		catch_err(sem_wait(philo->table->forks));
		print(philo->table, "%zd %d has taken a fork\n",
			get_timestamp(), philo->number);
		i++;
	}
	return (0);
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
