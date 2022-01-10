/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:41:28 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 00:13:13 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdlib.h>
#include "table.h"
#include "utils.h"

t_philo	*init_philosopher(t_table *table, int philo_number)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->number = philo_number;
	philo->table = table;
	philo->left_num_of_eat = table->settings->target_num_of_eat;
	philo->last_eat = get_millitime();
	if (pthread_mutex_init(&philo->mutex, NULL))
		return (del_philosopher(philo));
	return (philo);
}

t_philo	*del_philosopher(t_philo *philo)
{
	if (philo == NULL)
		return (NULL);
	pthread_mutex_destroy(&philo->mutex);
	free(philo);
	return (NULL);
}

t_philo	**init_philosophers(t_table *table)
{
	t_philo	**philos;
	int		i;

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

	i = 0;
	while (philos[i])
	{
		del_philosopher(philos[i]);
		i++;
	}
	free(philos);
	return (NULL);
}
