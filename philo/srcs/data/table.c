/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/07 00:09:33 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "philosopher.h"

t_table	*init_table(t_settings *settings, t_philosopher **philos)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->philos = philos;
	table->length = settings->num_of_philos;
	table->forks = (bool *)malloc(sizeof(bool) * (settings->num_of_philos));
	if (table->forks == NULL)
		return (NULL);
	i = 0;
	while (i < settings->num_of_philos)
		table->forks[i++] = true;
	return (table);
}

void	take_a_fork(t_table *table, int philo_num, enum e_fork_dir direction)
{
	int	fork_num;

	fork_num = philo_num + direction;
	if (fork_num >= table->length)
		fork_num = 0;
	table->forks[fork_num] = false;
	table->philos[philo_num]->forks[direction] = true;
	printf("timestamp_in_ms %d has taken a fork\n", philo_num);
}

void	return_a_fork(t_table *table, int philo_num, enum e_fork_dir direction)
{
	table->philos[philo_num]->forks[direction] = false;
	table->forks[philo_num + direction] = true;
}
