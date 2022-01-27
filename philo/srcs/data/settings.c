/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:36:21 by ywake             #+#    #+#             */
/*   Updated: 2022/01/28 01:13:53 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "utils.h"

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
		if (i == NUM_OF_PHILOS && (input < 1 || MAX_THREADS < input))
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

void	init_settings(t_settings *settings, int argc, char *argv[])
{
	settings->num_of_philos = ft_atoi(argv[NUM_OF_PHILOS], NULL);
	settings->time_to_die = ft_atoi(argv[TIME_TO_DIE], NULL);
	settings->time_to_eat = ft_atoi(argv[TIME_TO_EAT], NULL);
	settings->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP], NULL);
	if (argc == 6)
		settings->target_num_of_eat = ft_atoi(argv[TARGET_NUM_OF_EAT], NULL);
	else
		settings->target_num_of_eat = -1;
}
