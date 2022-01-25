/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:41:28 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 01:51:47 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "utils.h"

t_philo	*init_philosopher(t_table *table, int philo_number)
{
	t_philo	*philo;

	philo = (t_philo *)catch_null(malloc(sizeof(t_philo)));
	philo->number = philo_number;
	philo->table = table;
	philo->num_of_eat = 0;
	philo->last_eat = get_timestamp();
	if (pthread_mutex_init(&philo->mutex, NULL))
		return (del_philosopher(philo));
	return (philo);
}

t_philo	*del_philosopher(t_philo *philo)
{
	if (philo == NULL)
		return (NULL);
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_destroy(&philo->mutex);
	free(philo);
	return (NULL);
}

t_philo	**init_philosophers(t_table *table)
{
	t_philo	**philos;
	int		i;

	if (table == NULL)
		return (NULL);
	philos = (t_philo **)catch_null(
			malloc(sizeof(t_philo *) * (table->length + 1)));
	i = 0;
	while (i < table->length)
	{
		philos[i] = catch_null(init_philosopher(table, i));
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

bool	is_died(t_philo	*philo)
{
	t_timestamp	now;

	now = get_timestamp();
	if (now - philo->last_eat > philo->table->settings->time_to_die)
	{
		return (true);
	}
	return (false);
}
