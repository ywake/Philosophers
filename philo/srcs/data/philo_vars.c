/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:41:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/10 23:46:36 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_timestamp	last_eat(t_philo *philo)
{
	t_timestamp	last_eat;

	pthread_mutex_lock(&philo->mutex);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->mutex);
	return (last_eat);
}
