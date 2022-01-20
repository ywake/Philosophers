/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:57:39 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 13:46:01 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include "settings.h"

int	time_to_eat(t_table *table)
{
	int	time_to_eat;

	if (table == NULL || table->settings == NULL)
		return (0);
	pthread_mutex_lock(&table->mutexes[SETTINGS]);
	time_to_eat = table->settings->time_to_eat;
	pthread_mutex_unlock(&table->mutexes[SETTINGS]);
	return (time_to_eat);
}

int	time_to_sleep(t_table *table)
{
	int	time_to_sleep;

	if (table == NULL || table->settings == NULL)
		return (0);
	pthread_mutex_lock(&table->mutexes[SETTINGS]);
	time_to_sleep = table->settings->time_to_eat;
	pthread_mutex_unlock(&table->mutexes[SETTINGS]);
	return (time_to_sleep);
}

// has lock
void	set_finish(t_table *table)
{
	if (table == NULL)
		return ;
	pthread_mutex_lock(&table->mutexes[IS_FINISH]);
	table->is_finish = true;
	pthread_mutex_unlock(&table->mutexes[IS_FINISH]);
}

// has lock
bool	is_finish(t_table *table)
{
	bool	is_finish;

	if (table == NULL)
		return (true);
	pthread_mutex_lock(&table->mutexes[IS_FINISH]);
	is_finish = table->is_finish;
	pthread_mutex_unlock(&table->mutexes[IS_FINISH]);
	return (is_finish);
}
