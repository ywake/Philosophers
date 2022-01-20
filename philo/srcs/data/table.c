/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 14:23:58 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "settings.h"
#include "fork.h"
#include "utils.h"

t_table	*init_table(t_settings *settings)
{
	t_table	*table;
	int		i;

	if (settings == NULL)
		return (NULL);
	if (!set((void **)&table, malloc(sizeof(t_table))))
		return (NULL);
	table->settings = settings;
	table->length = settings->num_of_philos;
	table->is_finish = false;
	if (!set((void **)&table->forks, malloc(sizeof(t_fork *) * table->length)))
		return (del_table(table));
	i = 0;
	while (i < table->length)
		if (!set((void **)&table->forks[i++], init_fork()))
			return (del_table(table));
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
	while (table->forks && i < table->length && table->forks[i])
	{
		table->forks[i] = del_fork(table->forks[i]);
		i++;
	}
	free(table->forks);
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
	pthread_mutex_lock(&table->mutexes[PRINTF]);
	printf(fmt, time, number + 1);
	pthread_mutex_unlock(&table->mutexes[PRINTF]);
}
