/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:05:04 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 12:17:54 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdlib.h>

#include "settings.h"
#include "table.h"
#include "utils.h"

t_philo	*init_philosopher(t_settings *setting, t_table *table, int philo_number)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->settings = setting;
	philo->table = table;
	philo->number = philo_number;
	philo->left_num_of_eat = setting->target_num_of_eat;
	philo->last_eat = get_timestamp();
	return (philo);
}

t_philo	*del_philosopher(t_philo *philo)
{
	if (philo == NULL)
		return (NULL);
	philo->settings = NULL;
	philo->table = NULL;
	free(philo);
	return (NULL);
}

t_philo	**init_philosophers(t_settings *settings, t_table *table)
{
	t_philo	**philos;
	int		i;

	if (settings == NULL)
		return (NULL);
	philos = (t_philo **)malloc(
			sizeof(t_philo *) * (settings->num_of_philos + 1));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < settings->num_of_philos)
	{
		philos[i] = init_philosopher(settings, table, i);
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

t_timestamp	philo_eat_done(t_philo **philo)
{
	int	i;
	int	fork_num;

	if (!*philo)
		return (0);
	(*philo)->left_num_of_eat--;
	i = 0;
	while (i < 2 && (*philo)->table && (*philo)->table->forks)
	{
		fork_num = ((*philo)->number + i) % (*philo)->table->length;
		_return((*philo)->table->forks[fork_num]);
		i++;
	}
	return (10);
}
