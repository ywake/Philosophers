/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:41:28 by ywake             #+#    #+#             */
/*   Updated: 2022/01/07 00:09:46 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "settings.h"

t_philosopher	*init_philosopher(int number)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (philo == NULL)
		return (NULL);
	philo->number = number;
	philo->forks[0] = false;
	philo->forks[1] = false;
	return (philo);
}

t_philosopher	**init_philosophers(t_settings *settings)
{
	int				i;
	t_philosopher	**philos;

	philos = (t_philosopher **)malloc(
			sizeof(t_philosopher *) * settings->num_of_philos + 1);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < settings->num_of_philos)
	{
		philos[i] = init_philosopher(i);
		if (philos[i] == NULL)
			return (NULL);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

void	philo_eat(t_settings *settings, t_philosopher *philo)
{
	printf("timestamp_in_ms %d is eating\n", philo->number);
	usleep(settings->time_to_eat * 1000);
}

void	philo_sleep(t_settings *settings, t_philosopher *philo)
{
	printf("timestamp_in_ms %d is sleeping\n", philo->number);
	usleep(settings->time_to_sleep * 1000);
}

void	philo_think(t_settings *settings, t_philosopher *philo)
{
	(void)settings;
	printf("timestamp_in_ms %d is thinking\n", philo->number);
	usleep(1000);
}
