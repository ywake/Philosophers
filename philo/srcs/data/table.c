/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/10 12:53:14 by ywake            ###   ########.fr       */
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
	table->forks = (t_fork **)malloc(sizeof(t_fork *) * table->length);
	if (table->forks == NULL)
		return (del_table(table));
	i = 0;
	while (i < table->length)
		table->forks[i++] = init_fork();
	return (table);
}

t_table	*del_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->length)
	{
		table->forks[i] = del_fork(table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table);
	return (NULL);
}
