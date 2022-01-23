/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:33:45 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 13:06:36 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include "settings.h"
#include "table.h"
#include "philosopher.h"
#include "thread.h"
#include "utils.h"

t_philo	**initialize(int argc, char *argv[]);
int		my_abort(t_philo **philos, pthread_t *observer);
int		run_philos(t_philo **philos);
int		detach_philos(t_philo **philos);

int	main(int argc, char *argv[])
{
	pthread_t	observer;
	t_philo		**philos;

	if (set((void **)&philos, initialize(argc, argv)))
		return (1);
	if (pthread_create(&observer, NULL, observe, philos))
		return (1);
	if (run_philos(philos))
		return (my_abort(philos, &observer));
	if (detach_philos(philos))
		return (1);
	pthread_join(observer, NULL);
	return (0);
}

t_philo	**initialize(int argc, char *argv[])
{
	t_settings	*settings;
	t_table		*table;
	t_philo		**philos;

	if (validity_check(argc, argv) == false)
		return (NULL);
	if (set((void **)&settings, init_settings(argc, argv)))
		return (NULL);
	if (set((void **)&table, init_table(settings)))
		return ((t_philo **)del_settings(settings));
	if (set((void **)&philos, init_philosophers(settings, table)))
		return (del_settings(settings), (t_philo **)del_table(table));
	return (philos);
}

// Return 1
int	my_abort(t_philo **philos, pthread_t *observer)
{
	pthread_detach(*observer);
	detach_philos(philos);
	return (1);
}

// Returns 0 If seccess , -1 otherwise.
int	run_philos(t_philo **philos)
{
	int			i;
	int			num_of_philos;

	num_of_philos = philos[0]->settings->num_of_philos;
	i = 0;
	while (i < num_of_philos && philos[0] && !is_finish(&philos[0]->table))
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
