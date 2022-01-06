/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/06 22:48:15 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stddef.h>
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
	table->forks = (bool *)malloc(sizeof(bool) * (settings->num_of_philos + 1));
	if (table->forks == NULL)
		return (NULL);
	while (i < settings->num_of_philos)
	{
		table->forks[i] = true;
		i++;
	}
	table->forks[i] = NULL;
	return (table);
}
