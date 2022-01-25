/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:41:28 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 17:35:09 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdlib.h>

#include "settings.h"
#include "table.h"
#include "utils.h"

t_philo	*del_philosopher(t_philo *philo);

t_philo	*init_philosopher(t_settings *settings, t_table *table, int philo_num)
{
	t_philo	*philo;

	philo = (t_philo *)catch_null(malloc(sizeof(t_philo)));
	philo->settings = settings;
	philo->table = table;
	philo->number = philo_num;
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
	philo->settings = NULL;
	philo->table = NULL;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_destroy(&philo->mutex);
	free(philo);
	return (NULL);
}

t_philo	**init_philosophers(t_settings *settings, t_table *table)
{
	t_philo	**philos;
	int		i;

	if (table == NULL)
		return (NULL);
	philos = (t_philo **)catch_null(
			malloc(sizeof(t_philo *) * (settings->num_of_philos + 1)));
	i = 0;
	while (i < settings->num_of_philos)
	{
		philos[i] = catch_null(init_philosopher(settings, table, i));
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
