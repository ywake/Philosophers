/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:02 by ywake             #+#    #+#             */
/*   Updated: 2022/01/13 17:52:11 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "settings.h"
#include "utils.h"
#include "my_semaphore.h"

sem_t	*semaphore(const char *name, int initial_value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0600, initial_value);
	if (sem == SEM_FAILED)
		my_exit(1);
	return (sem);
}

t_table	*init_table(t_settings *settings)
{
	t_table	*table;

	if (settings == NULL)
		return (NULL);
	table = (t_table *)catch_null(malloc(sizeof(t_table)));
	table->settings = settings;
	table->length = settings->num_of_philos;
	table->forks = semaphore(FORKS_SEM, settings->num_of_philos);
	table->num_of_finish_philos = semaphore(FINS_SEM, 0);
	table->num_of_living_philos = semaphore(LIVES_SEM, settings->num_of_philos);
	table->printf = semaphore(PRINT_SEM, 1);
	return (table);
}

t_table	*del_table(t_table *table)
{
	if (table == NULL)
		return (NULL);
	catch_err(sem_close(table->forks));
	catch_err(sem_unlink(FORKS_SEM));
	catch_err(sem_close(table->num_of_finish_philos));
	catch_err(sem_unlink(FINS_SEM));
	catch_err(sem_close(table->num_of_living_philos));
	catch_err(sem_unlink(LIVES_SEM));
	catch_err(sem_close(table->printf));
	catch_err(sem_unlink(PRINT_SEM));
	free(table);
	return (NULL);
}

bool	is_all_live(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->length)
	{
		catch_err(sem_wait(table->num_of_living_philos));
		i++;
	}
	i = 0;
	while (i < table->length)
	{
		catch_err(sem_post(table->num_of_living_philos));
		i++;
	}
	return (true);
}

void	print(t_table *table, const char *fmt, t_timestamp time, int number)
{
	catch_err(sem_wait(table->printf));
	if (!is_all_live(table))
		return ;
	printf(fmt, time, number + 1);
	catch_err(sem_post(table->printf));
}
