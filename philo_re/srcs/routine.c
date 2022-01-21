/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:48:33 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 14:35:08 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include "table.h"

void	philo_eat(t_table **table, int philo_number)
{
	size_t	time;

	time = get_timestamp();
	if (*table)
		print(*table, "%zu %d is eating\n", time, philo_number);
	if (*table && (*table)->philos)
		set_last_eat(&(*table)->philos[philo_number], time);
	my_usleep(get_time_to_eat(*table) * 1000);
	if (*table && (*table)->philos)
		decrement_left_num_of_eat(&(*table)->philos[philo_number]);
}

void	philo_sleep(t_table **table, int philo_number)
{
	const char	*format_str;

	format_str = "%zu %d is sleeping\n";
	if (*table)
		print(*table, format_str, get_timestamp(), philo_number);
	if (*table)
		my_usleep(get_time_to_sleep(*table) * 1000);
}

void	philo_think(t_table **table, int philo_number)
{
	const char	*format_str;

	format_str = "%zu %d is thinking\n";
	if (*table)
		print(*table, format_str, get_timestamp(), philo_number);
}

void	take_forks(t_table **table, int philo_number)
{
	int			i;
	int			fork_num;
	const char	*fmt_str;

	fmt_str = "%zu %d has taken a fork\n";
	i = 0;
	while (i < 2)
	{
		if (*table == NULL || (*table)->forks == NULL)
			return ;
		fork_num = (philo_number + i) % (*table)->length;
		while (*table && (*table)->forks
			 && _take((*table)->forks[fork_num]) == false)
		{
			my_usleep(1000);
			if (*table == NULL || is_finish(*table))
				return ;
		}
		if (*table)
			print(*table, fmt_str, get_timestamp(), philo_number);
		i++;
	}
}

void	return_forks(t_table **table, int philo_number)
{
	int	i;
	int	fork_num;

	i = 0;
	while (i < 2)
	{
		if (!*table || !(*table)->forks)
			return ;
		fork_num = philo_number + i;
		if (fork_num >= (*table)->length)
			fork_num = 0;
		if (is_finish((*table)))
			return ;
		if (*table && (*table)->forks)
			_return((*table)->forks[fork_num]);
		i++;
	}
}
