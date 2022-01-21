/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:56:43 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 14:47:28 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	fork->ready = true;
	if (pthread_mutex_init(&fork->mutex, NULL))
		return (free(fork), NULL);
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

t_fork	**init_forks(size_t num)
{
	t_fork	**forks;
	size_t	i;

	forks = (t_fork **)ft_calloc(num + 1, sizeof(t_fork *));
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < num)
	{
		forks[i] = init_fork();
		if (forks[i] == NULL)
			return (del_forks(forks));
		i++;
	}
	return (forks);
}

t_fork	**del_forks(t_fork **forks)
{
	int	i;

	if (forks == NULL)
		return (NULL);
	i = 0;
	while (forks[i])
	{
		forks[i] = del_fork(forks[i]);
		i++;
	}
	free(forks);
	return (NULL);
}
