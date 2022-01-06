/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/07 00:10:38 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "settings.h"
#include "philosopher.h"
#include "table.h"
#include "process.h"

int	main(int argc, char *argv[])
{
	t_settings		settings;
	t_philosopher	**philos;
	t_table			*table;

	if (init_settings(&settings, argc, argv) == false)
		return (1);
	philos = init_philosophers(&settings);
	if (philos == NULL)
		return (1);
	table = init_table(&settings, philos);
	if (table == NULL)
		return (1);
	loop(&settings, table);
}
