/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:05:04 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 18:19:43 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdlib.h>
#include <string.h>

t_philo	*init_philosopher(t_settings *settings, int philo_number)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->number = philo_number;
	philo->left_num_of_eat = settings->target_num_of_eat;
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

t_philo	**init_philosophers(t_settings *settings)
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
		philos[i] = init_philosopher(settings, i);
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
