/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:42:12 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 12:40:01 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include <stdio.h>
#include "philosopher.h"
#include "table.h"

// need table lock
bool	is_died(t_philo **philo)
{
	t_timestamp	now;
	t_timestamp	past_time;

	if (*philo == NULL)
		return (false);
	now = get_timestamp();
	past_time = now - (*philo)->last_eat;
	if (*philo == NULL || (*philo)->settings == NULL)
		return (true);
	if (past_time > (*philo)->settings->time_to_die)
	{
		if ((*philo)->table == NULL)
			return (true);
		(*philo)->table->finish = true;
		printf("%zu %d died\n", now, (*philo)->number + 1);
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
	while (philos[0] && !is_finish(&philos[0]->table))
	{
		pthread_mutex_lock(&philos[0]->table->mutex);
		is_enough = true;
		i = 0;
		while (i < philos[0]->settings->num_of_philos)
		{
			if (is_died(&philos[i]))
				break ;
			if (is_enough && philos[i]->left_num_of_eat != 0)
				is_enough = false;
			i++;
		}
		if (is_enough && philos[0])
			philos[0]->table->finish = true;
		pthread_mutex_unlock(&philos[0]->table->mutex);
		my_usleep(10);
	}
	return (NULL);
}

typedef t_timestamp	(*t_func)(t_philo **philo);

void	*routine(void *arg)
{
	t_philo		**philo;
	t_func		*funcs;
	int			i;
	t_timestamp	time;

	philo = (t_philo **)arg;
	funcs = (t_func []){take_right_fork, take_left_fork, philo_eat,
		philo_eat_done, philo_sleep, philo_think};
	if ((*philo) && (*philo)->number % 2)
		my_usleep(250);
	i = 0;
	while (*philo)
	{
		pthread_mutex_lock(&(*philo)->table->mutex);
		if ((*philo)->table->finish)
		{
			pthread_mutex_unlock(&(*philo)->table->mutex);
			break ;
		}
		if (*philo)
			time = funcs[i](philo);
		if (*philo && (*philo)->table)
			pthread_mutex_unlock(&(*philo)->table->mutex);
		my_usleep(time);
		i = (i + 1) % 6;
	}
	return (NULL);
}
