/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:19:17 by ywake             #+#    #+#             */
/*   Updated: 2022/01/28 01:57:36 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

/**
 * Return Value
 * 0: Success
 * -1: Failed
 */
int	init_table(t_table *table, t_settings *settings)
{
	table->length = settings->num_of_philos;
	table->finish = false;
	if (set((void **)&table->forks, init_forks(settings->num_of_philos)))
		return (-1);
	if (pthread_mutex_init(&table->mutex, NULL))
		return (del_forks(table->forks), -1);
	return (0);
}

void	del_table(t_table *table)
{
	pthread_mutex_lock(&table->mutex);
	table->forks = del_forks(table->forks);
	pthread_mutex_unlock(&table->mutex);
	pthread_mutex_destroy(&table->mutex);
}

bool	is_finish(t_table *table)
{
	bool	is_finish;

	pthread_mutex_lock(&table->mutex);
	is_finish = table->finish;
	pthread_mutex_unlock(&table->mutex);
	return (is_finish);
}
