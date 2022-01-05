/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:18:46 by ywake             #+#    #+#             */
/*   Updated: 2022/01/05 22:49:50 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

#include <stddef.h>
#include "utils.h"

bool	init_data(t_settings *data, int argc, char *argv[])
{
	int	i;

	if (argc < 5)
		return (false);
	i = 0;
	while (argv[i])
		if (ft_atoi(argv[i++]) < 0)
			return (false);
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] == NULL)
		data->target_num_of_eat = -1;
	else
		data->target_num_of_eat = ft_atoi(argv[5]);
	return (true);
}
