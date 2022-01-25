/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:41:37 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 17:42:18 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

#include <stdlib.h>
#include <stdio.h>

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
	table->length = settings->num_of_philos;
	table->forks = semaphore(FORKS_SEM, settings->num_of_philos);
	table->num_of_finish_philos = semaphore(FINS_SEM, 0);
	table->everyone_is_alive = semaphore(LIVES_SEM, 1);
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
	catch_err(sem_close(table->everyone_is_alive));
	catch_err(sem_unlink(LIVES_SEM));
	catch_err(sem_close(table->printf));
	catch_err(sem_unlink(PRINT_SEM));
	free(table);
	return (NULL);
}

bool	is_all_live(t_table *table)
{
	catch_err(sem_wait(table->everyone_is_alive));
	catch_err(sem_post(table->everyone_is_alive));
	return (true);
}

void	print(t_table *table, const char *fmt, t_timestamp time, int number)
{
	catch_err(sem_wait(table->printf));
	// if (!is_all_live(table))
	// 	return ;
	printf(fmt, time, number + 1);
	catch_err(sem_post(table->printf));
}
