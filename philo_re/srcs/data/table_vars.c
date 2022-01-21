/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:47:23 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 17:54:07 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include "settings.h"

// has lock
int	get_time_to_eat(t_table *table)
{
	int	time_to_eat;

	if (table == NULL || table->settings == NULL)
		return (0);
	pthread_mutex_lock(&table->mutexes[TABLE_SETTINGS]);
	time_to_eat = table->settings->time_to_eat;
	pthread_mutex_unlock(&table->mutexes[TABLE_SETTINGS]);
	return (time_to_eat);
}

// has lock
int	get_time_to_sleep(t_table *table)
{
	int	time_to_sleep;

	if (table == NULL || table->settings == NULL)
		return (0);
	pthread_mutex_lock(&table->mutexes[TABLE_SETTINGS]);
	time_to_sleep = table->settings->time_to_eat;
	pthread_mutex_unlock(&table->mutexes[TABLE_SETTINGS]);
	return (time_to_sleep);
}

// has lock
void	set_finish(t_table *table)
{
	if (table == NULL)
		return ;
	pthread_mutex_lock(&table->mutexes[TABLE_IS_FINISH]);
	table->finish = true;
	pthread_mutex_unlock(&table->mutexes[TABLE_IS_FINISH]);
}

// has lock
bool	is_finish(t_table *table)
{
	bool	is_finish;

	if (table == NULL)
		return (true);
	pthread_mutex_lock(&table->mutexes[TABLE_IS_FINISH]);
	is_finish = table->finish;
	pthread_mutex_unlock(&table->mutexes[TABLE_IS_FINISH]);
	return (is_finish);
}
