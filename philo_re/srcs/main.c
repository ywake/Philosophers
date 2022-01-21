/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:33:45 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 02:50:16 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include "settings.h"
#include "table.h"
#include "thread.h"
#include "utils.h"

int	my_abort(t_table **table);

int	main(int argc, char *argv[])
{
	t_table	*table;
	int		i;

	if (validity_check(argc, argv) == false)
		return (1);
	if (set((void **)&table, init_table(argc, argv)))
		return (1);
	if (run_threads(&table))
		return (my_abort(&table));
	if (pthread_join(table->observer, NULL))
		return (my_abort(&table));
	i = 0;
	while (i < table->length)
		if (pthread_detach(table->philos[i++]->thread))
			return (my_abort(&table));
	table = del_table(table);
	return (0);
}

int	my_abort(t_table **table)
{
	*table = del_table(*table);
	return (1);
}
