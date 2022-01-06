/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:41:28 by ywake             #+#    #+#             */
/*   Updated: 2022/01/05 23:09:52 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>
#include <stdlib.h>
#include "settings.h"

t_philosopher	**init_philosopher(t_settings *settings)
{
	int				i;
	t_philosopher	**philos;

	philos = (t_philosopher **)malloc(
			sizeof(t_philosopher *) * settings->num_of_philos + 1);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (settings->num_of_philos < i)
	{
		philos[i] = (t_philosopher *)malloc(sizeof(t_philosopher));
		if (philos[i] == NULL)
			return (NULL);
		philos[i]->number = i;
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

void	eat(t_philosopher *philo)
{
	printf("timestamp_in_ms %d is eating\n", philo->number);
}

void	sleep(t_philosopher *philo)
{
	printf("timestamp_in_ms %d is sleeping\n", philo->number);
}

void	think(t_philosopher *philo)
{
	printf("timestamp_in_ms %d is thinking\n", philo->number);
}
