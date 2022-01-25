/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:31:58 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 17:41:28 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

#include <stdlib.h>

#include "table.h"
#include "philosopher.h"

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
	{
		pthread_detach(thread[OBSERVER]);
		pthread_detach(thread[PHILOSOPHER]);
		exit(1);
	}
	sem_post(philo->table->num_of_finish_philos);
	exit(0);
}

void	*philo_action(void *arg)
{
	t_philo		*philo;
	t_func		*funcs;
	t_timestamp	sleep_time;
	int			i;

	philo = (t_philo *)arg;
	funcs = (t_func []){
		take_forks, philo_eat, philo_sleep, philo_think, NULL,
	};
	i = 0;
	while (true)
	{
		pthread_mutex_lock(&philo->mutex);
		sleep_time = funcs[i](philo);
		pthread_mutex_unlock(&philo->mutex);
		my_usleep(sleep_time);
		if (funcs[++i] == NULL)
			i = 0;
	}
	return (NULL);
}

void	*philo_observe(void	*arg)
{
	t_philo		*philo;
	t_timestamp	now;
	bool		is_dead;

	philo = (t_philo *)arg;
	while (true)
	{
		pthread_mutex_lock(&philo->mutex);
		now = get_timestamp();
		is_dead = now - philo->last_eat > philo->settings->time_to_die;
		if (is_dead)
		{
			catch_err(sem_wait(philo->table->everyone_is_alive));
			print(philo->table, "%zd %d died\n", now, philo->number);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		my_usleep(1000);
	}
	return (NULL);
}
