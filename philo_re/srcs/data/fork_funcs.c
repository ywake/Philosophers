/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:40:07 by ywake             #+#    #+#             */
/*   Updated: 2022/01/24 12:17:21 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

// has lock
bool	try_take_a_fork(t_fork *fork)
{
	bool	there_was_a_fork;

	if (fork == NULL)
		return (false);
	pthread_mutex_lock(&fork->mutex);
	there_was_a_fork = fork->ready;
	if (there_was_a_fork)
		fork->ready = false;
	pthread_mutex_unlock(&fork->mutex);
	return (there_was_a_fork);
}

// has lock
void	drop_a_fork(t_fork *fork)
{
	if (fork == NULL)
		return ;
	pthread_mutex_lock(&fork->mutex);
	fork->ready = true;
	pthread_mutex_unlock(&fork->mutex);
}
