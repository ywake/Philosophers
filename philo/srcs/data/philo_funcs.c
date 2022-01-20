/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:06:50 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 14:35:48 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>
#include "table.h"
#include "utils.h"

void	philo_eat(t_philo **philo)
{
	size_t	time;

	time = get_timestamp();
	if (*philo)
		print((*philo)->table, "%zu %d is eating\n", time, (*philo)->number);
	set_last_eat(philo, time);
	if (*philo && (*philo)->table)
		my_usleep(time_to_eat((*philo)->table) * 1000);
	decrement_left_num_of_eat(philo);
}

void	philo_sleep(t_philo **philo)
{
	const char	*format_str;

	format_str = "%zu %d is sleeping\n";
	if (*philo)
		print((*philo)->table, format_str, get_timestamp(), (*philo)->number);
	if (*philo && (*philo)->table)
		my_usleep(time_to_sleep((*philo)->table) * 1000);
}

void	philo_think(t_philo **philo)
{
	const char	*format_str;

	format_str = "%zu %d is thinking\n";
	if (*philo)
		print((*philo)->table, format_str, get_timestamp(), (*philo)->number);
}

void	take_forks(t_philo **philo)
{
	int			i;
	int			fork_num;
	const char	*fmt_str;

	fmt_str = "%zu %d has taken a fork\n";
	i = 0;
	while (i < 2)
	{
		if (!*philo || !(*philo)->table || !(*philo)->table->forks)
			return ;
		fork_num = (*philo)->number + i;
		if (fork_num >= (*philo)->table->length)
			fork_num = 0;
		while (*philo && (*philo)->table && (*philo)->table->forks
			&& _take((*philo)->table->forks[fork_num]) == false)
		{
			my_usleep(1000);
			if (*philo == NULL
				 || is_finish(table(philo)))
				return ;
		}
		if (*philo)
			print((*philo)->table, fmt_str, get_timestamp(), (*philo)->number);
		i++;
	}
}

void	return_forks(t_philo **philo)
{
	int	i;
	int	fork_num;

	i = 0;
	while (i < 2)
	{
		if (!*philo || !(*philo)->table || !(*philo)->table->forks)
			return ;
		fork_num = (*philo)->number + i;
		if (fork_num >= (*philo)->table->length)
			fork_num = 0;
		if (is_finish((*philo)->table))
			return ;
		if (*philo && (*philo)->table && (*philo)->table->forks)
			_return((*philo)->table->forks[fork_num]);
		i++;
	}
}
