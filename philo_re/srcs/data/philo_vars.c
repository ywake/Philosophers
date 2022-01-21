/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:20:52 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 14:48:40 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// has lock
t_timestamp	get_last_eat(t_philo **philo)
{
	t_timestamp	last_eat;

	if (*philo == NULL)
		return (0);
	pthread_mutex_lock(&(*philo)->mutexes[LAST_EAT]);
	last_eat = (*philo)->last_eat;
	pthread_mutex_unlock(&(*philo)->mutexes[LAST_EAT]);
	return (last_eat);
}

// has lock
void	set_last_eat(t_philo **philo, t_timestamp last_eat)
{
	if (*philo == NULL)
		return ;
	pthread_mutex_lock(&(*philo)->mutexes[LAST_EAT]);
	(*philo)->last_eat = last_eat;
	pthread_mutex_unlock(&(*philo)->mutexes[LAST_EAT]);
}

// has lock
int	get_left_num_of_eat(t_philo **philo)
{
	int	left_num_of_eat;

	if (*philo == NULL)
		return (0);
	pthread_mutex_lock(&(*philo)->mutexes[LEFT_NUM_OF_EAT]);
	left_num_of_eat = (*philo)->left_num_of_eat;
	pthread_mutex_unlock(&(*philo)->mutexes[LEFT_NUM_OF_EAT]);
	return (left_num_of_eat);
}

// has lock
void	decrement_left_num_of_eat(t_philo **philo)
{
	if (philo == NULL || *philo == NULL)
		return ;
	pthread_mutex_lock(&(*philo)->mutexes[LEFT_NUM_OF_EAT]);
	if ((*philo)->left_num_of_eat > 0)
		(*philo)->left_num_of_eat--;
	pthread_mutex_unlock(&(*philo)->mutexes[LEFT_NUM_OF_EAT]);
}
