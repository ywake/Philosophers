/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/10 23:42:13 by ywake            ###   ########.fr       */
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

t_philo	**initialize(int argc, char *argv[]);
void	*routine(void *arg);
void	*observe(void *arg);

int	main(int argc, char *argv[])
{
	t_philo		**philos;
	pthread_t	observer;
	int			i;

	philos = initialize(argc, argv);
	if (philos == NULL)
		return (1);
	i = 0;
	while (i < philos[0]->table->length)
	{
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]))
			return (1);
		if (pthread_detach(philos[i++]->thread))
			return (1);
	}
	pthread_create(&observer, NULL, observe, philos);
	pthread_join(observer, NULL);
	del_settings(philos[0]->table->settings);
	del_table(philos[0]->table);
	del_philosophers(philos);
	return (0);
}

t_philo	**initialize(int argc, char *argv[])
{
	t_settings	*settings;
	t_table		*table;
	t_philo		**philos;

	if (argc != 5 && argc != 6)
		return (NULL);
	settings = init_settings(argc, argv);
	if (settings == NULL)
		return (NULL);
	table = init_table(settings);
	if (table == NULL)
	{
		del_settings(settings);
		return (NULL);
	}
	philos = init_philosophers(table);
	if (philos == NULL)
	{
		del_settings(settings);
		del_table(table);
		return (NULL);
	}
	return (philos);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2)
		my_usleep(125);
	while (is_someone_died(philo->table) == false)
	{
		take_forks(philo);
		philo_eat(philo);
		return_forks(philo);
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
		now = get_millitime();
		i = 0;
		while (i < philos[0]->table->length)
		{
			if (now - last_eat(philos[i]) > time_to_die)
			{
				someone_died(philos[i]->table);
				printf("%zu %d died\n", get_millitime(), i);
				return (NULL);
			}
			i++;
		}
	}
}
