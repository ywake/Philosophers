/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:06:50 by ywake             #+#    #+#             */
/*   Updated: 2022/01/09 13:35:13 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>
#include <unistd.h>
#include "table.h"
#include "utils.h"

void	philo_eat(t_table *table, int philo_number)
{
	printf("%lld %d is eating\n", get_millitime(), philo_number);
	usleep(table->settings->time_to_eat * 1000);
}

void	philo_sleep(t_table *table, int philo_number)
{
	printf("%lld %d is sleeping\n", get_millitime(), philo_number);
	usleep(table->settings->time_to_sleep * 1000);
}

void	philo_think(t_table *table, int philo_number)
{
	(void)table;
	printf("%lld %d is thinking\n", get_millitime(), philo_number);
	// usleep(1000 * 1000);
}
