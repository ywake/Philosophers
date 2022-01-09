/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/09 23:19:51 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "settings.h"
#include "philosopher.h"
#include "table.h"
#include "utils.h"

void	*routine(void *arg);
void	*observe(void *arg);

int	main(int argc, char *argv[])
{
	t_settings	settings;
	t_table		*table;
	t_philo		**philos;
	pthread_t	observer;
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
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]))
			return (1);
		if (pthread_detach(philos[i++]->thread))
			return (1);
	}
	pthread_create(&observer, NULL, observe, philos);
	pthread_join(observer, NULL);
	del_table(table);
	del_philosophers(philos);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_forks(philo->table, philo->number);
		philo_eat(philo);
		return_forks(philo->table, philo->number);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*observe(void *arg)
{
	int		i;
	t_philo	**philos;
	size_t	now;
	size_t	time_to_die;

	philos = (t_philo **)arg;
	time_to_die = (size_t)philos[0]->table->settings->time_to_die;
	while (1)
	{
		usleep(1000 * 1000);
		now = get_millitime();
		i = 0;
		while (i < philos[0]->table->length)
		{
			if (now - philos[i]->last_eat > time_to_die)
			{
				philo_dead(philos[i]);
				printf("%zu %d died\n", now, i);
				return (NULL);
			}
			i++;
		}
	}
}
