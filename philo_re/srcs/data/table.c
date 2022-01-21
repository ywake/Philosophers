/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:19:17 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 14:47:01 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

t_table	*init_table(int argc, char *argv[])
{
	t_table	*table;
	int		i;

	if (set((void **)&table, ft_calloc(1, sizeof(t_table))))
		return (NULL);
	if (set((void **)&table->settings, init_settings(argc, argv)))
		return (del_table(table));
	if (set((void **)&table->philos, init_philosophers(table->settings)))
		return (del_table(table));
	if (set((void **)&table->forks, init_forks(table->settings->num_of_philos)))
		return (del_table(table));
	table->length = table->settings->num_of_philos;
	memset(&table->observer, 0, sizeof(pthread_t));
	i = 0;
	while (i < TABLE_MUTEX_LEN)
		if (pthread_mutex_init(&table->mutexes[i++], NULL))
			return (del_table(table));
	return (table);
}

t_table	*del_table(t_table *table)
{
	int	i;

	if (table == NULL)
		return (NULL);
	i = 0;
	while (i < TABLE_MUTEX_LEN)
		pthread_mutex_lock(&table->mutexes[i++]);
	i = 0;
	while (i < table->length)
		table->forks[i] = del_fork(table->forks[i]), i++;
	free(table->forks);
	table->forks = NULL;
	table->philos = del_philosophers(table->philos);
	table->settings = del_settings(table->settings);
	i = 0;
	while (i < TABLE_MUTEX_LEN)
	{
		pthread_mutex_unlock(&table->mutexes[i]);
		pthread_mutex_destroy(&table->mutexes[i]);
		i++;
	}
	free(table);
	return (NULL);
}

// has lock
void	print(t_table *table, const char *fmt, t_timestamp time, int number)
{
	if (table == NULL || is_finish(table))
		return ;
	pthread_mutex_lock(&table->mutexes[TABLE_PRINTF]);
	printf(fmt, time, number + 1);
	pthread_mutex_unlock(&table->mutexes[TABLE_PRINTF]);
}
