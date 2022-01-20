/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:41:28 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 14:23:37 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "table.h"
#include "utils.h"

t_philo	*init_philosopher(t_table *table, int philo_number)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->number = philo_number;
	philo->table = table;
	philo->left_num_of_eat = table->settings->target_num_of_eat;
	memset(&philo->thread, 0, sizeof(pthread_t));
	philo->last_eat = get_timestamp();
	i = 0;
	while (i < PHILO_MUTEX_LEN)
		if (pthread_mutex_init(&philo->mutexes[i++], NULL))
			return (del_philosopher(philo));
	return (philo);
}

t_philo	*del_philosopher(t_philo *philo)
{
	int	i;

	if (philo == NULL)
		return (NULL);
	i = 0;
	while (i < PHILO_MUTEX_LEN)
	{
		pthread_mutex_lock(&philo->mutexes[i]);
		pthread_mutex_unlock(&philo->mutexes[i]);
		pthread_mutex_destroy(&philo->mutexes[i]);
		i++;
	}
	free(philo);
	return (NULL);
}

t_philo	**init_philosophers(t_table *table)
{
	t_philo	**philos;
	int		i;

	if (table == NULL)
		return (NULL);
	philos = (t_philo **)malloc(sizeof(t_philo *) * (table->length + 1));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < table->length)
	{
		philos[i] = init_philosopher(table, i);
		if (philos[i] == NULL)
			return (del_philosophers(philos));
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

t_philo	**del_philosophers(t_philo **philos)
{
	int	i;

	if (philos == NULL)
		return (NULL);
	i = 0;
	while (philos[i])
	{
		philos[i] = del_philosopher(philos[i]);
		i++;
	}
	free(philos);
	return (NULL);
}

// has lock
bool	is_died(t_philo	**philo)
{
	t_timestamp	now;
	t_timestamp	past_time;

	now = get_timestamp();
	past_time = now - last_eat(philo);
	if (!*philo || !(*philo)->table || !(*philo)->table->settings)
		return (true);
	if (past_time > (*philo)->table->settings->time_to_die)
	{
		set_finish((*philo)->table);
		if (*philo == NULL || (*philo)->table == NULL)
			return (true);
		pthread_mutex_lock(&(*philo)->table->mutexes[PRINTF]);
		printf("%zu %d died\n", now, (*philo)->number + 1);
		pthread_mutex_unlock(&(*philo)->table->mutexes[PRINTF]);
		return (true);
	}
	return (false);
}
