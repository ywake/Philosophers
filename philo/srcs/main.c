/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 12:11:54 by ywake            ###   ########.fr       */
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
int		clean(t_philo **philos);
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
	if (pthread_create(&observer, NULL, observe, philos))
		return (clean(philos));
	i = 0;
	while (i < philos[0]->table->length)
	{
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]))
			return (clean(philos));
		if (pthread_detach(philos[i++]->thread))
			return (clean(philos));
	}
	pthread_join(observer, NULL);
	clean(philos);
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
	table = init_table(settings);
	philos = init_philosophers(table);
	if (philos == NULL)
		return (del_settings(settings), (t_philo **)del_table(table));
	return (philos);
}

int	clean(t_philo **philos)
{
	del_settings(philos[0]->table->settings);
	del_table(philos[0]->table);
	del_philosophers(philos);
	return (1);
}

typedef void	(*t_func)(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;
	t_func	*funcs;
	int		i;

	philo = (t_philo *)arg;
	funcs = (t_func []){
		take_forks, philo_eat, return_forks, philo_sleep, philo_think};
	if (philo->number % 2)
		my_usleep(250);
	i = 0;
	while (is_finish(philo->table) == false)
	{
		funcs[i](philo);
		i = (i + 1) % 5;
	}
	return (NULL);
}

void	*observe(void *arg)
{
	int		i;
	t_philo	**philos;
	bool	flg_finish;

	philos = (t_philo **)arg;
	while (!is_finish(philos[0]->table))
	{
		i = 0;
		flg_finish = true;
		while (i < philos[0]->table->length)
		{
			if (is_died(philos[i]))
				return (NULL);
			if (flg_finish && left_num_of_eat(philos[i]) != 0)
				flg_finish = false;
			i++;
		}
		if (flg_finish)
			set_finish(philos[0]->table);
		my_usleep(1000);
	}
	return (NULL);
}
