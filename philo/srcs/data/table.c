/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 02:30:16 by ywake            ###   ########.fr       */
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
	table->is_someone_died = false;
	table->forks = (t_fork **)malloc(sizeof(t_fork *) * table->length);
	if (table->forks == NULL)
		return (del_table(table));
	i = 0;
	while (i < table->length)
		table->forks[i++] = init_fork();
	if (pthread_mutex_init(&table->mutex, NULL))
		return (del_table(table));
	return (table);
}

t_table	*del_table(t_table *table)
{
	int	i;

	i = 0;
	while (table->forks && i < table->length)
	{
		table->forks[i] = del_fork(table->forks[i]);
		i++;
	}
	free(table->forks);
	pthread_mutex_destroy(&table->mutex);
	free(table);
	return (NULL);
}

void	someone_died(t_table *table)
{
	pthread_mutex_lock(&table->mutex);
	table->is_someone_died = true;
	pthread_mutex_unlock(&table->mutex);
}

bool	is_someone_died(t_table *table)
{
	bool	is_someone_died;

	pthread_mutex_lock(&table->mutex);
	is_someone_died = table->is_someone_died;
	pthread_mutex_unlock(&table->mutex);
	return (is_someone_died);
}

void	print(t_table *table, const char *fmt, t_timestamp time, int number)
{
	pthread_mutex_lock(&table->printf_mutex);
	printf(fmt, time, number);
	pthread_mutex_unlock(&table->printf_mutex);
}
