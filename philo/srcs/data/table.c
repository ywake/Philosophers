/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:19:17 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 11:19:34 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

t_table	*init_table(t_settings *settings)
{
	t_table	*table;

	if (set((void **)&table, ft_calloc(1, sizeof(t_table))))
		return (NULL);
	table->length = settings->num_of_philos;
	if (set((void **)&table->forks, init_forks(settings->num_of_philos)))
		return (del_table(table));
	if (pthread_mutex_init(&table->mutex, NULL))
		return (del_table(table));
	return (table);
}

t_table	*del_table(t_table *table)
{
	if (table == NULL)
		return (NULL);
	pthread_mutex_lock(&table->mutex);
	table->forks = del_forks(table->forks);
	pthread_mutex_unlock(&table->mutex);
	pthread_mutex_destroy(&table->mutex);
	free(table);
	return (NULL);
}

bool	is_finish(t_table **table)
{
	bool	is_finish;

	if (*table == NULL)
		return (true);
	pthread_mutex_lock(&(*table)->mutex);
	is_finish = (*table)->finish;
	pthread_mutex_unlock(&(*table)->mutex);
	return (is_finish);
}
