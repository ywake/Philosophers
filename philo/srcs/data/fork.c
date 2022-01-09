/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:38:15 by ywake             #+#    #+#             */
/*   Updated: 2022/01/09 13:26:07 by ywake            ###   ########.fr       */
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
	fork->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (fork->mutex == NULL)
		return (del_fork(fork));
	if (pthread_mutex_init(fork->mutex, NULL))
		return (del_fork(fork));
	return (fork);
}

t_fork	*del_fork(t_fork *fork)
{
	if (fork == NULL)
		return (NULL);
	if (fork->mutex != NULL)
		pthread_mutex_destroy(fork->mutex);
	free(fork->mutex);
	free(fork);
	return (NULL);
}

bool	_take(t_fork *fork)
{
	bool	old_ready;
	bool	res;

	if (pthread_mutex_lock(fork->mutex))
		return (false);
	old_ready = fork->ready;
	if (fork->ready)
		fork->ready = false;
	res = old_ready != fork->ready;
	if (pthread_mutex_unlock(fork->mutex))
		return (false);
	return (res);
}

bool	_return(t_fork *fork)
{
	if (pthread_mutex_lock(fork->mutex))
		return (false);
	fork->ready = true;
	if (pthread_mutex_unlock(fork->mutex))
		return (false);
	return (true);
}
