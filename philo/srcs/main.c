/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/09 13:35:17 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "settings.h"
#include "philosopher.h"
#include "table.h"
#include "utils.h"

void	*routine(void *arg);

int	main(int argc, char *argv[])
{
	t_settings	settings;
	t_table		*table;
	t_philo		**philos;
	int			i;

	if (init_settings(&settings, argc, argv) == false)
		return (1);
	table = init_table(&settings);
	if (table == NULL)
		return (1);
	philos = init_philosophers(table);
	if (philos == NULL)
		return (1);
	i = 0;
	while (i < table->length)
	{
		if (pthread_create(philos[i]->thread, NULL, routine, philos[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < table->length)
		if (pthread_join(*(philos[i++]->thread), NULL))
			return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_forks(philo->table, philo->number);
		philo_eat(philo->table, philo->number);
		return_forks(philo->table, philo->number);
		philo_sleep(philo->table, philo->number);
		philo_think(philo->table, philo->number);
	}
	return (NULL);
}
