/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 02:25:16 by ywake             #+#    #+#             */
/*   Updated: 2022/01/16 11:24:43 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "settings.h"
#include "table.h"
#include "philosopher.h"
#include "utils.h"

#define CHILD (0)

t_philo	**initialize(int argc, char *argv[]);
int		clear(t_philo **philos, pid_t *pids);
void	job(t_philo *philo);
void	observe(t_table *table);

int	main(int argc, char *argv[])
{
	t_philo	**philos;
	pid_t	*pids;
	int		i;

	errno = 0;
	philos = initialize(argc, argv);
	pids = (pid_t *)catch_null(
			malloc(sizeof(pid_t) * (philos[0]->table->length + 1)));
	i = -1;
	while (++i < philos[0]->table->length + 1)
	{
		pids[i] = catch_err(fork());
		if (pids[i] == CHILD && i == 0)
			observe(philos[0]->table);
		else if (pids[i] == CHILD)
			job(philos[i - 1]);
	}
	i = -1;
	while (++i < philos[0]->table->length + 1)
	{
		catch_err(waitpid(-1, NULL, 0));
		if (i == 0)
			kill_all_child(pids, philos[0]->table->length + 1);
	}
	return (clear(philos, pids));
}

t_philo	**initialize(int argc, char *argv[])
{
	t_settings	*settings;
	t_table		*table;
	t_philo		**philos;

	if (validity_check(argc, argv) == false)
		exit(1);
	settings = init_settings(argc, argv);
	table = init_table(settings);
	philos = init_philosophers(table);
	if (philos == NULL)
		my_exit(1);
	return (philos);
}

int	clear(t_philo **philos, pid_t *pids)
{
	if (philos == NULL)
		return (0);
	free(pids);
	del_settings(philos[0]->table->settings);
	del_table(philos[0]->table);
	del_philosophers(philos);
	return (0);
}

typedef void	(*t_func)(t_philo *philo);

void	job(t_philo *philo)
{
	t_func	*funcs;
	int		i;

	funcs = (t_func []){take_forks, philo_eat, philo_sleep, philo_think};
	i = 0;
	while (true)
	{
		if (is_died(philo))
		{
			catch_err(sem_wait(philo->table->num_of_living_philos));
			printf("%zu %d died\n", get_timestamp(), philo->number + 1);
			exit(0);
		}
		if (philo->num_of_eat == philo->table->settings->target_num_of_eat)
			catch_err(sem_post(philo->table->num_of_finish_philos));
		funcs[i](philo);
		i = (i + 1) % 4;
	}
}

void	observe(t_table *table)
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
