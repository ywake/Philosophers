/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:18:46 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 11:21:42 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

#include <stdlib.h>
#include "utils.h"

t_settings	*init_settings(int argc, char *argv[])
{
	t_settings	*settings;
	int			i;

	if (argc < 5)
		return (NULL);
	i = 0;
	while (argv[i])
		if (ft_atoi(argv[i++]) < 0)
			return (NULL);
	settings = (t_settings *)malloc(sizeof(t_settings));
	if (settings == NULL)
		return (NULL);
	settings->num_of_philos = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] == NULL)
		settings->target_num_of_eat = -1;
	else
		settings->target_num_of_eat = ft_atoi(argv[5]);
	if (settings->num_of_philos < 1)
		return (del_settings(settings));
	return (settings);
}

t_settings	*del_settings(t_settings *settings)
{
	free(settings);
	return (NULL);
}
