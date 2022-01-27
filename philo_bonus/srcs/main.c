/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:20:04 by ywake             #+#    #+#             */
/*   Updated: 2022/01/27 23:56:50 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "settings.h"
#include "table.h"
#include "philosopher.h"
#include "jobs.h"
#include "utils.h"

t_philo	**initialize(int argc, char *argv[]);
pid_t	*start_simulation(t_philo **philos);
void	end_simulation(t_philo **philos, pid_t *pids);
void	clear(t_philo ***philos, pid_t **pids);

int	main(int argc, char *argv[])
{
	t_philo	**philos;
	pid_t	*pids;

	if (!validity_check(argc, argv))
		return (1);
	philos = initialize(argc, argv);
	pids = start_simulation(philos);
	end_simulation(philos, pids);
	clear(&philos, &pids);
}

t_philo	**initialize(int argc, char *argv[])
{
	t_settings	*settings;
	t_table		*table;
	t_philo		**philos;

	settings = init_settings(argc, argv);
	table = init_table(settings);
	philos = init_philosophers(settings, table);
	if (philos == NULL)
		my_exit(1);
	return (philos);
}

#define CHILD (0)

pid_t	*start_simulation(t_philo **philos)
{
	pid_t	*pids;
	int		i;

	pids = (pid_t *)catch_null(malloc(
				sizeof(pid_t) * ((size_t)philos[0]->table->length + 1)));
	i = 0;
	while (i < philos[0]->table->length + 1)
	{
		pids[i] = catch_err(fork());
		if (pids[i] == CHILD)
		{
			if (i == 0)
				observe_job(philos[0]->table);
			else
				philo_job(philos[i - 1]);
		}
		i++;
	}
	return (pids);
}

void	end_simulation(t_philo **philos, pid_t *child_pids)
{
	size_t	length;
	size_t	i;
	int		status;

	length = (size_t)philos[0]->settings->num_of_philos + 1;
	i = 0;
	while (i < length)
	{
		catch_err(waitpid(-1, &status, 0));
		if (i == 0)
		{
			catch_err(sem_wait(philos[0]->table->printf));
			kill_all_child(child_pids, length);
		}
		i++;
	}
}

void	clear(t_philo ***philos, pid_t **pids)
{
	t_settings	*settings;
	t_table		*table;

	settings = (*philos)[0]->settings;
	table = (*philos)[0]->table;
	*philos = del_philosophers(*philos);
	del_table(table);
	del_settings(settings);
	free(*pids);
	*pids = NULL;
}
