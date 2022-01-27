/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:42:12 by ywake             #+#    #+#             */
/*   Updated: 2022/01/28 01:48:47 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include <stdio.h>
#include "philosopher.h"
#include "table.h"

// need table lock
bool	is_died(t_philo *philo)
{
	t_timestamp	now;
	t_timestamp	past_time;

	now = get_timestamp();
	past_time = now - philo->last_eat;
	if (past_time > philo->settings->time_to_die)
	{
		philo->table->finish = true;
		printf("%zu %d died\n", now, philo->number + 1);
		return (true);
	}
	return (false);
}

void	*observe(void *arg)
{
	t_philo	**philos;
	int		i;
	bool	is_enough;

	philos = (t_philo **)arg;
	while (!is_finish(philos[0]->table))
	{
		pthread_mutex_lock(&philos[0]->table->mutex);
		is_enough = true;
		i = 0;
		while (i < philos[0]->settings->num_of_philos)
		{
			if (is_died(philos[i]))
				break ;
			if (is_enough && philos[i]->left_num_of_eat != 0)
				is_enough = false;
			i++;
		}
		if (is_enough)
			philos[0]->table->finish = true;
		pthread_mutex_unlock(&philos[0]->table->mutex);
		my_usleep(1000);
	}
	return (NULL);
}

typedef t_timestamp	(*t_func)(t_philo *philo);

void	*routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;
	t_func		*funcs;
	int			i;
	t_timestamp	time;

	philo = (t_philo *)arg;
	table = philo->table;
	funcs = (t_func []){take_right_fork, take_left_fork,
		philo_eat, philo_sleep, philo_think};
	if (philo->number % 2)
		my_usleep(250);
	i = 0;
	while (!is_finish(table))
	{
		pthread_mutex_lock(&table->mutex);
		time = funcs[i](philo);
		pthread_mutex_unlock(&table->mutex);
		my_usleep(time * (1 - 2 * (time < 0)));
		if (time >= 0)
			i = (i + 1) % 5;
	}
	return (NULL);
}
