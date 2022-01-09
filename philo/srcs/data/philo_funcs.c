/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:06:50 by ywake             #+#    #+#             */
/*   Updated: 2022/01/09 13:35:13 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>
#include <unistd.h>
#include "utils.h"

void	philo_eat(t_philo *philo)
{
	size_t	time;

	time = get_millitime();
	printf("%zu %d is eating\n", time, philo->number);
	philo->last_eat = time;
	usleep(philo->table->settings->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	printf("%zu %d is sleeping\n", get_millitime(), philo->number);
	usleep(philo->table->settings->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	printf("%zu %d is thinking\n", get_millitime(), philo->number);
	// usleep(1000 * 1000);
}
