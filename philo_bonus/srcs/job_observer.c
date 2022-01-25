/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_observer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:28:47 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 18:07:19 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>

#include "table.h"
#include "utils.h"

#include <stdio.h>
void	observe_job(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->length)
	{
		catch_err(sem_wait(table->num_of_finish_philos));
		i++;
	}
	exit(0);
}

void	kill_all_child(pid_t *pids, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		kill(pids[i], SIGINT);
		i++;
	}
}
