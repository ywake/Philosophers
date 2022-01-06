/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/05 23:04:09 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "settings.h"
#include "philosopher.h"

int	main(int argc, char *argv[])
{
	t_settings		settings;
	t_philosopher	**philos;

	if (init_settings(&settings, argc, argv) == false)
		return (1);
	philos = init_philosopher(&settings);
	if (philos == NULL)
		return (1);
}
