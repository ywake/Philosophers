/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:20:20 by ywake             #+#    #+#             */
/*   Updated: 2022/01/06 23:57:36 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

#include "settings.h"
#include "table.h"

void	loop(t_settings *settings, t_table *table)
{
	while (1)
	{
		take_a_fork(table, 0, RIGHT);
		take_a_fork(table, 0, LEFT);
		philo_eat(settings, table->philos[0]);
		return_a_fork(table, 0, RIGHT);
		return_a_fork(table, 0, LEFT);
		philo_sleep(settings, table->philos[0]);
		philo_think(settings, table->philos[0]);
	}
}
