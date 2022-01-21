/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:42:12 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 16:09:48 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include <stdio.h>
#include "table.h"

// Returns 0 If seccess , -1 otherwise.
int	run_threads(t_table **table)
{
	int	i;

	if (pthread_create(&(*table)->observer, NULL, observe, table))
		return (-1);
	i = 0;
	while (i < (*table)->length && !is_finish(*table))
	{
		pthread_mutex_lock(&(*table)->mutexes[TABLE_TMP_PHILOS_NUM]);
		(*table)->tmp_philos_number = i;
		if (pthread_create(
				&(*table)->philos[i++]->thread, NULL, routine, table))
			return (-1);
	}
	return (0);
}

// has lock
bool	is_died(t_table **table, t_philo **philo)
{
	t_timestamp	now;
	t_timestamp	past_time;

	now = get_timestamp();
	past_time = now - get_last_eat(philo);
	if (*table == NULL || (*table)->settings == NULL)
		return (true);
	if (past_time > (*table)->settings->time_to_die)
	{
		set_finish(*table);
		if (*table == NULL)
			return (true);
		pthread_mutex_lock(&(*table)->mutexes[TABLE_PRINTF]);
		printf("%zu %d died\n", now, (*philo)->number + 1);
		pthread_mutex_unlock(&(*table)->mutexes[TABLE_PRINTF]);
		return (true);
	}
	return (false);
}

void	*observe(void *arg)
{
	t_table	**table;
	int		i;
	bool	flg_finish;

	table = (t_table **)arg;
	while (*table && !is_finish(*table))
	{
		i = 0;
		flg_finish = true;
		while (*table && i < (*table)->length)
		{
			if ((*table)->philos[i] == NULL
				|| is_died(table, &(*table)->philos[i]))
				return (NULL);
			if (flg_finish && get_left_num_of_eat(&(*table)->philos[i]) != 0)
				flg_finish = false;
			i++;
		}
		if (flg_finish && *table)
			set_finish(*table);
		my_usleep(300);
	}
	return (NULL);
}

typedef void	(*t_func)(t_table **table, int philo_number);

void	*routine(void *arg)
{
	t_table	**table;
	t_func	*funcs;
	int		i;
	int		philo_number;

	table = (t_table **)arg;
	philo_number = (*table)->tmp_philos_number;
	pthread_mutex_unlock(&(*table)->mutexes[TABLE_TMP_PHILOS_NUM]);
	funcs = (t_func []){
		take_forks, philo_eat, return_forks, philo_sleep, philo_think
	};
	if (philo_number % 2)
		my_usleep(250);
	i = 0;
	while (*table && !is_finish(*table))
	{
		funcs[i](table, philo_number);
		i = (i + 1) % 5;
	}
	return (NULL);
}
