/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:33:45 by ywake             #+#    #+#             */
/*   Updated: 2022/01/31 09:30:52 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include "settings.h"
#include "table.h"
#include "philosopher.h"
#include "thread.h"
#include "utils.h"

t_philo	**initialize(int argc, char *argv[], t_settings *stg, t_table *table);
int		my_abort(t_philo **philos, pthread_t *observer);
int		run_philos(t_philo **philos);
int		detach_philos(t_philo **philos);

int	main(int argc, char *argv[])
{
	pthread_t	observer;
	t_settings	settings;
	t_table		table;
	t_philo		**philos;

	if (set((void **)&philos, initialize(argc, argv, &settings, &table)))
		return (1);
	if (pthread_create(&observer, NULL, observe, philos))
		return (my_abort(philos, NULL));
	if (run_philos(philos))
		return (my_abort(philos, &observer));
	if (detach_philos(philos))
		return (my_abort(philos, &observer));
	if (pthread_join(observer, NULL))
		return (my_abort(philos, &observer));
	my_abort(philos, NULL);
	return (0);
}

t_philo	**initialize(int argc, char **argv, t_settings *setting, t_table *table)
{
	t_philo		**philos;

	if (validity_check(argc, argv) == false)
		return (NULL);
	init_settings(setting, argc, argv);
	if (init_table(table, setting))
		return (NULL);
	if (set((void **)&philos, init_philosophers(setting, table)))
		return (del_table(table), NULL);
	return (philos);
}

// Return 1
int	my_abort(t_philo **philos, pthread_t *observer)
{
	if (observer != NULL)
	{
		pthread_detach(*observer);
		detach_philos(philos);
	}
	del_table(philos[0]->table);
	del_philosophers(philos);
	return (1);
}

// Returns 0 If seccess , -1 otherwise.
int	run_philos(t_philo **philos)
{
	int			i;
	int			num_of_philos;

	num_of_philos = philos[0]->settings->num_of_philos;
	i = 0;
	while (i < num_of_philos && philos[0] && !is_finish(philos[0]->table))
	{
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]))
			return (-1);
		i++;
	}
	return (0);
}

// Returns 0 If seccess , -1 otherwise.
int	detach_philos(t_philo **philos)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (philos[i])
		if (pthread_detach(philos[i++]->thread))
			res = -1;
	return (res);
}
