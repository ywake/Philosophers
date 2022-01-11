/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:41:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 10:47:35 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_timestamp	last_eat(t_philo *philo)
{
	t_timestamp	last_eat;

	if (philo == NULL)
		return (0);
	pthread_mutex_lock(&philo->mutex);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->mutex);
	return (last_eat);
}

void	set_last_eat(t_philo *philo, t_timestamp last_eat)
{
	if (philo == NULL)
		return ;
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = last_eat;
	pthread_mutex_unlock(&philo->mutex);
}

int	left_num_of_eat(t_philo *philo)
{
	int	left_num_of_eat;

	if (philo == NULL)
		return (0);
	pthread_mutex_lock(&philo->mutex);
	left_num_of_eat = philo->left_num_of_eat;
	pthread_mutex_unlock(&philo->mutex);
	return (left_num_of_eat);
}

void	decrement_left_num_of_eat(t_philo *philo)
{
	if (philo == NULL)
		return ;
	pthread_mutex_lock(&philo->mutex);
	if (philo->left_num_of_eat > 0)
		philo->left_num_of_eat--;
	pthread_mutex_unlock(&philo->mutex);
}
