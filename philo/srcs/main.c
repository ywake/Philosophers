/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/06 22:53:51 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "settings.h"
#include "philosopher.h"
#include "table.h"

int	main(int argc, char *argv[])
{
	t_settings		settings;
	t_philosopher	**philos;
	t_table			*table;

	if (init_settings(&settings, argc, argv) == false)
		return (1);
	philos = init_philosopher(&settings);
	if (philos == NULL)
		return (1);
	table = init_table(&settings, philos);
	if (table == NULL)
		return (1);
}
