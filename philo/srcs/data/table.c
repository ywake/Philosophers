/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/18 14:22:55 by ywake            ###   ########.fr       */
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
	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->settings = settings;
	table->length = settings->num_of_philos;
	table->is_finish = false;
	table->forks = (t_fork **)malloc(sizeof(t_fork *) * table->length);
	if (table->forks == NULL)
		return (del_table(table));
	i = 0;
	while (i < table->length)
	{
		table->forks[i] = init_fork();
		if (table->forks[i++] == NULL)
			return (del_table(table));
	}
	if (pthread_mutex_init(&table->mutex, NULL)
		|| pthread_mutex_init(&table->printf_mutex, NULL))
		return (del_table(table));
	return (table);
}

t_table	*del_table(t_table *table)
{
	int	i;

	if (table == NULL)
		return (NULL);
	pthread_mutex_lock(&table->mutex);
	pthread_mutex_lock(&table->printf_mutex);
	i = 0;
	while (table->forks && i < table->length && table->forks[i])
	{
		table->forks[i] = del_fork(table->forks[i]);
		i++;
	}
	free(table->forks);
	pthread_mutex_unlock(&table->mutex);
	pthread_mutex_destroy(&table->mutex);
	pthread_mutex_unlock(&table->printf_mutex);
	pthread_mutex_destroy(&table->printf_mutex);
	free(table);
	return (NULL);
}

// has lock
void	set_finish(t_table *table)
{
	if (table == NULL)
		return ;
	pthread_mutex_lock(&table->mutex);
	table->is_finish = true;
	pthread_mutex_unlock(&table->mutex);
}

// has lock
bool	is_finish(t_table *table)
{
	bool	is_finish;

	if (table == NULL)
		return (true);
	pthread_mutex_lock(&table->mutex);
	is_finish = table->is_finish;
	pthread_mutex_unlock(&table->mutex);
	return (is_finish);
}

// has lock
void	print(t_table *table, const char *fmt, t_timestamp time, int number)
{
	if (table == NULL || is_finish(table))
		return ;
	pthread_mutex_lock(&table->printf_mutex);
	printf(fmt, time, number + 1);
	pthread_mutex_unlock(&table->printf_mutex);
}
