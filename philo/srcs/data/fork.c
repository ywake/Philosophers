/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:38:15 by ywake             #+#    #+#             */
/*   Updated: 2022/01/18 14:19:36 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fork.h"

t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	fork->ready = true;
	if (pthread_mutex_init(&fork->mutex, NULL))
		return (del_fork(fork));
	return (fork);
}

t_fork	*del_fork(t_fork *fork)
{
	if (fork == NULL)
		return (NULL);
	pthread_mutex_lock(&fork->mutex);
	pthread_mutex_unlock(&fork->mutex);
	pthread_mutex_destroy(&fork->mutex);
	free(fork);
	return (NULL);
}

// has lock
bool	_take(t_fork *fork)
{
	bool	there_is_a_fork;

	if (fork == NULL)
		return (false);
	pthread_mutex_lock(&fork->mutex);
	there_is_a_fork = fork->ready;
	if (there_is_a_fork)
		fork->ready = false;
	pthread_mutex_unlock(&fork->mutex);
	return (there_is_a_fork);
}

// has lock
void	_return(t_fork *fork)
{
	if (fork == NULL)
		return ;
	pthread_mutex_lock(&fork->mutex);
	fork->ready = true;
	pthread_mutex_unlock(&fork->mutex);
}
