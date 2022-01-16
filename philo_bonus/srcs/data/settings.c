/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:18:46 by ywake             #+#    #+#             */
/*   Updated: 2022/01/16 10:48:52 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

#include <stdlib.h>
#include <semaphore.h>
#include "utils.h"

#define MAX_PHILOS (100)

#ifdef __lilsnux__
# define SEM_VALUE_MAX (32767)
#endif

t_settings	*init_settings(int argc, char *argv[])
{
	t_settings	*settings;
	int			i;
	bool		overflow;

	if (argc < 5)
		return (NULL);
	i = 0;
	while (argv[i])
		if (ft_atoi(argv[i++], &overflow) < 0 || overflow)
			return (NULL);
	settings = (t_settings *)catch_null(malloc(sizeof(t_settings)));
	settings->num_of_philos = ft_atoi(argv[1], NULL);
	settings->time_to_die = ft_atoi(argv[2], NULL);
	settings->time_to_eat = ft_atoi(argv[3], NULL);
	settings->time_to_sleep = ft_atoi(argv[4], NULL);
	if (argv[5] == NULL)
		settings->target_num_of_eat = -1;
	else
		settings->target_num_of_eat = ft_atoi(argv[5], NULL);
	if (settings->num_of_philos < 1 || SEM_VALUE_MAX < settings->num_of_philos
		|| settings->target_num_of_eat == 0)
		exit(1);
	return (settings);
}

t_settings	*del_settings(t_settings *settings)
{
	free(settings);
	return (NULL);
}
