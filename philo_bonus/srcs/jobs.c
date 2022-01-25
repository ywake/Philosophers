/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:49:33 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 12:49:09 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <pthread.h>
#include <stdlib.h>
#include "utils.h"

void	*philo_action(void	*arg);
void	*philo_observe(void	*arg);

typedef t_timestamp	(*t_func)(t_philo *philo);

enum	e_thread_num
{
	OBSERVER,
	PHILOSOPHER,
	LEN,
};

void	philo_job(t_philo *philo)
{
	pthread_t	thread[LEN];

	if (pthread_create(&thread[OBSERVER], NULL, philo_observe, philo)
		|| pthread_create(&thread[PHILOSOPHER], NULL, philo_action, philo)
		|| pthread_detach(thread[PHILOSOPHER])
		|| pthread_join(thread[OBSERVER], NULL))
		exit(1);
	exit(0);
}

void	*philo_action(void	*arg)
{
	t_philo		*philo;
	t_func		*funcs;
	t_timestamp	time;
	int			i;

	philo = (t_philo *)arg;
	funcs = (t_func []){take_forks, philo_eat, philo_sleep, philo_think};
	i = 0;
	while (true)
	{
		pthread_mutex_lock(&philo->mutex);
		time = funcs[i](philo);
		if (philo->num_of_eat == philo->table->settings->target_num_of_eat)
			catch_err(sem_post(philo->table->num_of_finish_philos));
		pthread_mutex_unlock(&philo->mutex);
		my_usleep(time);
		i = (i + 1) % 4;
	}
}

void	*philo_observe(void	*arg)
{
	t_philo		*philo;
	const char	*format_str;

	format_str = "%zu %d died\n";
	philo = (t_philo *)arg;
	while (true)
	{
		pthread_mutex_lock(&philo->mutex);
		if (is_died(philo))
		{
			print(philo->table, format_str, get_timestamp(), philo->number);
			catch_err(sem_wait(philo->table->everyone_is_alive));
			break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		my_usleep(1000);
	}
	return (NULL);
}

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
