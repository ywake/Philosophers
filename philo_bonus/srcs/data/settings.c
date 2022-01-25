/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:18:46 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 15:26:59 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

#include <stdlib.h>
#include <semaphore.h>
#include <limits.h>
#include "utils.h"

#ifdef __linux__
# define SEM_VALUE_MAX (32767)
#endif

enum	e_args
{
	NUM_OF_PHILOS = 1,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	TARGET_NUM_OF_EAT,
};

bool	validity_check(int argc, char *argv[])
{
	int		i;
	int		input;
	bool	overflow;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		input = ft_atoi(argv[i], &overflow);
		if (input < 0 || overflow)
			return (false);
		if (i == NUM_OF_PHILOS && (input < 1 || SEM_VALUE_MAX < input))
			return (false);
		if (i == TARGET_NUM_OF_EAT && input == 0)
			return (false);
		if (i != NUM_OF_PHILOS && i != TARGET_NUM_OF_EAT
			&& (unsigned int)input > INT_MAX / 1000)
			return (false);
		i++;
	}
	return (true);
}

t_settings	*init_settings(int argc, char *argv[])
{
	t_settings	*settings;

	settings = (t_settings *)catch_null(malloc(sizeof(t_settings)));
	settings->num_of_philos = ft_atoi(argv[NUM_OF_PHILOS], NULL);
	settings->time_to_die = ft_atoi(argv[TIME_TO_DIE], NULL);
	settings->time_to_eat = ft_atoi(argv[TIME_TO_EAT], NULL);
	settings->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP], NULL);
	if (argc == 6)
		settings->target_num_of_eat = ft_atoi(argv[TARGET_NUM_OF_EAT], NULL);
	else
		settings->target_num_of_eat = -1;
	return (settings);
}

t_settings	*del_settings(t_settings *settings)
{
	free(settings);
	return (NULL);
}
